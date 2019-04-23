#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/itd.h"
#include "../include/node.h"


int readITD(const char* fichier, Image* imgPPM, ItdColorInstruction itdInstructions[], Node nodesArray[], int* nbOfNodes) {

	/***** VARIABLES *****/

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



	/***** CODE *****/

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

	//Link nodes
	for(int i = 0; i < *nbOfNodes; i++) {
		for(int j = 4; j < nbIntegers[i]; j++) {
			linkNode(&nodesArray[i], &nodesArray[values[i][j]]);
		}
	}
}