#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../include/itd.h"
#include "../include/node.h"


int readITD(const char* fichier, Image* imgPPM, ItdColorInstruction itdInstructions[], Node nodesArray[], int* nbOfNodes) {
	///// VARIABLES

	//ITD Code (first line)
	int version; //Version of ITD Code
	char code[5] = {0}; //ITD Code

	//Comments (second line)
	int reader;

	//PPM (third line)
	char ppmFileName[30] = {0}; //Name of the PPM File
	char ppmPath[50] = "images/";

	//Instructions (4-8th line)
	char instruction[10] = {0}; //Temporary variable used to read the instruction's name
	int instructionRed, instructionGreen, instructionBlue; //Temporary variables used to read the instruction's colors	

	//Number of nodes (9th line)
	*nbOfNodes = 0; //Presumed number of nodes

	//Nodes lines (remaining lines)
	int k = 0; //Iterator for line number
	char line[80] = {0}; //Used to read the nodes lines
	char delim[2] = " "; //Character which separate the integers in the string (here, a space)
	char *token; //Pointer to the first character after a delimiter character (here, a space)
	int values[MAX_NODES][MAX_NODES+4] = {0}; //Temporary integers' array used to stock the read values : [1st] is the line number (node number) / [2nd] is the integer number inside the line 
	int nbIntegers[MAX_NODES+4] = {0}; //Number of integers in the line [x]



	///// CODE

	//Open a file
	FILE* F = fopen(fichier,"r");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}
			//printf("Nom du fichier : %s\n", fichier);

	//Read the ITD code
	if(fscanf(F,"%s %d\n", code, &version) != 2){
		fprintf(stderr, "Error during the ITD code reading.\n");
		exit(EXIT_FAILURE);
	}

	//Check if the file has the good ITD code
	if(code[0] != '@' || code[1] != 'I' || code[2] != 'T' || code[3] != 'D'){
		fprintf(stderr, "The file is not a ITD map.\n");
		exit(EXIT_FAILURE);
	}
			//printf("Nom du code : %s %d\n", code, version);

	//Skip comments
	reader = getc(F);
	//If the first character is a #, it reads the whole line and goes to the next one
	while (reader == '#'){
		while(getc(F) != '\n');
		reader = getc(F);
	}
	ungetc(reader, F);

	//Read the PPM file line
	if(fscanf(F,"%s\n", ppmFileName) != 1){
		fprintf(stderr, "Error during the PPM line reading.\n");
		exit(EXIT_FAILURE);
	}
			//printf("%s\n", ppmFileName);

	//Check if the file is a PPM
	if(strstr(ppmFileName, ".ppm") == NULL) {
		fprintf(stderr, "Error : the file is not a PPM.\n");
		exit(EXIT_FAILURE);
	}

	//Fill the Image
	strcat(ppmPath, ppmFileName);
	loadImage(imgPPM, ppmPath);

	//Read the five instructions
	for(int i = 0; i < 5; i++) {
		if(fscanf(F,"%s %d %d %d\n", instruction, &instructionRed, &instructionGreen, &instructionBlue) != 4){
			fprintf(stderr, "Error during the instruction reading.\n");
			exit(EXIT_FAILURE);
		}

		//Check if values are between 0 and 255
		if(instructionRed < 0 || instructionRed > 255) {
			fprintf(stderr, "Red value from instruction out of 0-255\n");
			exit(EXIT_FAILURE);
		}
		if(instructionGreen < 0 || instructionGreen > 255) {
			fprintf(stderr, "Green value from instruction out of 0-255\n");
			exit(EXIT_FAILURE);
		}
		if(instructionBlue < 0 || instructionBlue > 255) {
			fprintf(stderr, "Blue value from instruction out of 0-255\n");
			exit(EXIT_FAILURE);
		}

		if(strcmp(instruction, "chemin") != 0 && strcmp(instruction, "noeud") != 0 && strcmp(instruction, "construct") != 0 && strcmp(instruction, "in") != 0 && strcmp(instruction, "out") != 0) {
			fprintf(stderr, "Error : ITD instructions don't have the right names\n");
			exit(EXIT_FAILURE);
		}

		for(int j = 0; j < 10; j++) {
			itdInstructions[i].name[j] = instruction[j]; 
		}
		itdInstructions[i].r = instructionRed;
		itdInstructions[i].g = instructionGreen;
		itdInstructions[i].b = instructionBlue;
	}

			/*
			//Printf the five instructions' values
			for(int i = 0; i < NUMBER_INSTRUCT; i++) {
				printf("%s : %d %d %d\n", itdInstructions[i].name, itdInstructions[i].r, itdInstructions[i].g, itdInstructions[i].b);
			}
			*/
		
	//Read number of nodes
	if(fscanf(F,"%d\n", nbOfNodes) != 1) {
		fprintf(stderr, "Error during the 'number of nodes' reading.\n");
		exit(EXIT_FAILURE);
	}
	if(*nbOfNodes >= MAX_NODES) {
		fprintf(stderr, "Error: too many nodes. The number of nodes must be less than 20.\n");
		exit(EXIT_FAILURE);
	}

	//Read nodes lines
	k = 0;
	//Read a line in the file and stock the content in the string 'line'
	while(fgets(line, 80, F) != NULL) { 
		token = strtok(line, delim); 
		while(token != NULL) {
			values[k][nbIntegers[k]] = atoi(token); //Fill the array with the read values for the line 'k' with the position of the current integer
			token = strtok(NULL, delim);
			nbIntegers[k]++;
		}
		k++;
	}
			/*
			for(int i = 0; i < k; i++) {
				for(int z = 0; z < nbIntegers[i]; z++) {
					printf("%d ", values[i][z]);
				}	
				printf("\n");
			}
			*/

	//Compare if number of nodes = number of lines
	if(*nbOfNodes != k) {
		fprintf(stderr, "Error, the number of nodes written was not exact.\n");
		exit(EXIT_FAILURE);
	}

	//Create nodes
	for(int i = 0; i < *nbOfNodes; i++) {
		nodesArray[i] = createNode(values[i][0], values[i][1], values[i][2], values[i][3]);
	}

	//Check if the nodes descriptions are valid
	checkNodesDescriptions(nodesArray, nbOfNodes, imgPPM, itdInstructions);

	//Check if there is at least one IN and only one OUT node
	doInAndOutExist(nodesArray, nbOfNodes);

	//Link nodes
	for(int i = 0; i < *nbOfNodes; i++) {
		for(int j = 4; j < nbIntegers[i]; j++) {
			linkNode(&nodesArray[i], &nodesArray[values[i][j]]);
		}
	}

	//Check if there is a path between every neighboor nodes
	for(int i = 0; i < *nbOfNodes; i++) {
		printf("Node n° %d : \n", i);
		checkAllPathsAroundANode(nodesArray[i], imgPPM, itdInstructions);
		printf("\n");
	}

	//Check if there is a path from the INs to the OUT
	isTherePathFromINtoOUT(nodesArray, nbOfNodes);

	//Remove all the marks
	deleteAllMarksOnNodes(nodesArray, nbOfNodes);


	return EXIT_SUCCESS;
}

int checkNodesDescriptions(Node nodesArray[], int* nbOfNodes, Image* imgPPM, ItdColorInstruction itdInstructions[]) {
	///// VARIABLES

	//For the coordinates check
	int max_x = imgPPM->w;
	int max_y = imgPPM->h;

	//For the type check
	int itd_x, itd_y, itd_type;
	int redSubpix, greenSubpix, blueSubpix;
	int itd_redComponent, itd_greenComponent, itd_blueComponent;


	///// CODE 
	
	//Check if the types are possible (1, 2, 3 or 4)
	for(int i = 0; i < *nbOfNodes; i++) {
		if(nodesArray[i].type != 1 && nodesArray[i].type != 2 && nodesArray[i].type != 3 && nodesArray[i].type != 4) {
			fprintf(stderr, "Error : incorrect nodes' types\n");
			exit(EXIT_FAILURE);
		}
	}

	//Check if the coords are valid
	for(int i = 0; i < *nbOfNodes; i++) {
		if(nodesArray[i].x < 0 || nodesArray[i].x > max_x || nodesArray[i].y < 0 || nodesArray[i].y > max_y) {
			fprintf(stderr, "Error : incorrect nodes' coordinates\n");
			exit(EXIT_FAILURE);
		}
	}

	//Check the nodes' types in function of the color pixel in the PPM
	//Type 1 should be a "in"
	//Type 2 should be a "out"
	//Type 3 and 4 should be a "noeud"
	for(int i = 0; i < *nbOfNodes; i++) {
		//Get the coords and the the type of the current node
		itd_x = nodesArray[i].x;
		itd_y = nodesArray[i].y;
		itd_type = nodesArray[i].type;

		//Get the colors of the subpixels (in the PPM) which correspond to the nodes coords
		redSubpix = (int) imgPPM->pixel[itd_y*(imgPPM->w) + itd_x].r;
		greenSubpix = (int) imgPPM->pixel[itd_y*(imgPPM->w) + itd_x].g;
		blueSubpix = (int) imgPPM->pixel[itd_y*(imgPPM->w) + itd_x].b;

		//Get the color of each ITD instructions and compare it to the subpixels colors to get the name of the current instruction
		for(int j = 0; j < NUMBER_INSTRUCT; j++) {
			itd_redComponent = itdInstructions[j].r;
			itd_greenComponent = itdInstructions[j].g;
			itd_blueComponent = itdInstructions[j].b;

			if(redSubpix == itd_redComponent && greenSubpix == itd_greenComponent && blueSubpix == itd_blueComponent) {
				if(strcmp(itdInstructions[j].name, "in") == 0 && itd_type == 1) break;
				else if(strcmp(itdInstructions[j].name, "out") == 0 && itd_type == 2) break;
				else if(strcmp(itdInstructions[j].name, "noeud") == 0 && itd_type == 3) break;
				else if(strcmp(itdInstructions[j].name, "noeud") == 0 && itd_type == 4) break;
				else {
					fprintf(stderr, "Error : ITD infos don't correspond to PPM pixels\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}


//Path are only vertical or horizontal. They are never diagonal. VERSION 1
int checkPathBetween2Nodes(Node node1, Node node2, Image* imgPPM, ItdColorInstruction itdInstructions[]) {
	///// VARIABLES

	int path_redComponent = -1, path_greenComponent = -1, path_blueComponent = -1; //color values of the path (-1 at the beginning to be sure it's gonna work after)

	int current_pos; //current pixel during the traveling 
	int red_value, green_value, blue_value; //values of the current pixel during the traveling

	Node min_node;
	int offset;


	///// CODE

	//Attribute the colors to the path variables from the ITD instructions
	for(int i = 0; i < NUMBER_INSTRUCT; i++) {
		if(strcmp(itdInstructions[i].name, "chemin") == 0) {
			path_redComponent = itdInstructions[i].r;
			path_greenComponent = itdInstructions[i].g;
			path_blueComponent = itdInstructions[i].b;
		}
	}

			/*
			printf("path values : %d %d %d\n", path_redComponent, path_greenComponent, path_blueComponent);
			*/


	//Check if the nodes have the same spot
	if(node1.x == node2.x && node1.y == node2.y) {
		fprintf(stderr, "Error: both nodes have the same coords\n");
		exit(EXIT_FAILURE);
	}

	//If path is vertical
	if(node1.x == node2.x) {
		offset = abs(node1.y - node2.y);

		min_node = node1; //min_node is firstly equal to node1
		//If the 'y' value of node2 is inferior to the 'y' value of min_node
		if(node2.y < min_node.y) {
			min_node = node2;
		}

		//Between 1 and offset because we don't want to check the color of the start node and end node (not a path color)
		for(int i = 1; i < offset; i++) {
			current_pos = (min_node.y * imgPPM->w + min_node.x) + i*imgPPM->w;
			red_value = imgPPM->pixel[current_pos].r;
			green_value = imgPPM->pixel[current_pos].g;
			blue_value = imgPPM->pixel[current_pos].b;

			if(red_value != path_redComponent || green_value != path_greenComponent || blue_value != path_blueComponent) {
				fprintf(stderr, "Error: there's no vertical path between those 2 nodes\n");
				exit(EXIT_FAILURE);
			}
			else {
				printf("There is a vertical path between those 2 nodes.\n");
				break;
			}
		}
	}

	//If path is horizontal
	if(node1.y == node2.y) {
		offset = abs(node1.x - node2.x);

		min_node = node1; //min_node is firstly equal to node1
		//If the 'x' value of node2 is inferior to the 'x' value of min_node
		if(node2.x < min_node.x) {
			min_node = node2;
		}

		for(int i = 1; i < offset; i++) {
			current_pos = (min_node.y * imgPPM->w + min_node.x) + i;
			red_value = imgPPM->pixel[current_pos].r;
			green_value = imgPPM->pixel[current_pos].g;
			blue_value = imgPPM->pixel[current_pos].b;

			if(red_value != path_redComponent || green_value != path_greenComponent || blue_value != path_blueComponent) {
				fprintf(stderr, "Error: there's no horizontal path between those 2 nodes\n");
				exit(EXIT_FAILURE);
			}
			else {
				printf("There is a horizontal path between those 2 nodes.\n");
				break;
			}
		}
	}

	//If the nodes don't have one same coord
	if(node1.x != node2.x && node1.y != node2.y) {
		fprintf(stderr, "The nodes are not on the same horizontal/vertical line\n");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}


int checkAllPathsAroundANode(Node root, Image* imgPPM, ItdColorInstruction itdInstructions[]) {
	///// VARIABLES 

	Node* current_child;
	Link* tmp_link = NULL;


	///// CODE

	if(root.link->node) {
		current_child = root.link->node;
		tmp_link = root.link;
		checkPathBetween2Nodes(root, *current_child, imgPPM, itdInstructions);

		while(tmp_link->next) {
			current_child = tmp_link->next->node;
			checkPathBetween2Nodes(root, *current_child, imgPPM, itdInstructions);

			tmp_link = tmp_link->next;
		}

		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "Error : no path around the node\n");
		exit(EXIT_FAILURE);
	}
}