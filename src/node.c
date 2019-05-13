#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "../include/node.h"
#include "../include/const.h"
#include "../include/window.h"
#include "../include/tower.h"

Node createNode(int value, int type, int x, int y) {
	Node node;

	node.value = value;
	node.type = type;
	node.x = x;
	node.y = y;

	node.win_x = gridCoordToWindowCoord(node.x);
	node.win_y = gridCoordToWindowCoord(node.y);

	node.marqued = 0; // 0=false / 1=true

	return node;
}

//If linkNode is used, we must use freeAllLinks at the end on this node.link
void linkNode(Node* root, Node* child) {
	if(root->link == NULL) { //If there's no link to the root, we create one with the child
		root->link = malloc(sizeof(Link));

		if(!root->link) {
			fprintf(stderr, "Bad allocation memory for link.\n");
			exit(EXIT_FAILURE);
		}

		root->link->node = child;
		root->link->next = NULL;
	}
	else addLink(root->link, child);
}

//Show all the informations about a node
void printNodeInfo(Node node) {
	printf("Noeud %d, type %d, position grille(%d,%d)/position fenetre(%d, %d). ", node.value, node.type, node.x, node.y, node.win_x, node.win_y);
	if(node.marqued == 1) {
		printf("Le noeud est marqué. ");
	}
	else if(node.marqued == 0) {
		printf("Le noeud n'est pas marqué. ");
	}
	printf("Minvalarc actuel : %d ", node.minValarc);
	if(node.link != NULL) {
		printf("Il est relié à : ");
		printNodeLinks(node.link);
		printf("Valarcs correspondants : ");
		printValarc(node.link);
	}
	if(node.previousPath != NULL){
		printf("Node précédent pour le chemin le plus court : %d", node.previousPath->value);
	}

	printf("\n \n");
}


int doInAndOutExist(Node nodesArray[], int* nbOfNodes) {
	///// VARIABLES

	int in = 0, out = 0;

	
	///// CODE

	for(int i = 0; i < *nbOfNodes; i++) {
		if(nodesArray[i].type == 1) {
			in++;
		}
		if(nodesArray[i].type == 2) {
			out++;
		}
	}

	if(out != 1) {
		fprintf(stderr, "Error : there is not only one OUT node...\n");
		exit(EXIT_FAILURE);
	}

	if(in >= 1 && out == 1) {
		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "Error : IN and OUT node...\n");
		exit(EXIT_FAILURE);
	}
}


int isTherePathFromINtoOUT(Node nodesArray[], int* nbOfNodes) {
	///// VARIABLES
	Node* nodesIN[MAX_NODES];
	int nbOfNodesIN = 0;

	Node* nodeOUT = NULL;


	///// CODE

	//Get all the nodes IN
	for(int i = 0; i < *nbOfNodes; i++) {
		//If the node is a IN
		if(nodesArray[i].type == 1) {
			nodesIN[nbOfNodesIN] = &nodesArray[i];
			nbOfNodesIN++;
		}
	}

	//Get the only node OUT
	for(int i = 0; i < *nbOfNodes; i++) {
		//If the node is a OUT
		if(nodesArray[i].type == 2) {
			nodeOUT = &nodesArray[i];
			break;
		}
	}

	//For each node IN
	for(int i = 0; i < nbOfNodesIN; i++) {
		deleteAllMarksOnNodes(nodesArray, nbOfNodes); //Delete all the marks on the nodes
		depthFirstSearchFromRoot(nodesArray, nbOfNodes, nodesIN[i]); //Mark all the nodes accessible from the root 'nodesIN[i]'

		//If the out area is marked, it means we can access it from the current IN area
		if(nodeOUT->marqued == 1) {
			printf("The OUT area is accessible from the IN area (node n° %d).\n", nodesIN[i]->value);
		}
		else {
			fprintf(stderr, "Error: the OUT area is not accessible from the IN area (node n° %d).\n", nodesIN[i]->value);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}


// Put a mark on the nodes  -- NEED TO CALL the deleteMarks function after
int depthFirstSearchFromRoot(Node nodesArray[], int* nbOfNodes, Node* root) {
	///// VARIABLES
	Node* current_child;
	Link* tmp_link = NULL;


	///// CODE

	//Put the mark on the current node
	root->marqued = 1;

	//Recursive algorithm
	if(root->link->node) {
		current_child = root->link->node;
		tmp_link = root->link;
		if(current_child->marqued != 1) {
			depthFirstSearchFromRoot(nodesArray, nbOfNodes, current_child);
		}
		
		while(tmp_link->next) {
			current_child = tmp_link->next->node;
			if(current_child->marqued != 1) {
				depthFirstSearchFromRoot(nodesArray, nbOfNodes, current_child);
			}

			tmp_link = tmp_link->next;
		}

		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "Error during the Depth First Search\n");
		exit(EXIT_FAILURE);
	}
}

int deleteAllMarksOnNodes(Node nodesArray[], int* nbOfNodes) {
	for(int i = 0; i < *nbOfNodes; i++) {
		nodesArray[i].marqued = 0;
	}

	return EXIT_SUCCESS;
}

/*
//Travel every path pixel from one node to another
int travelPathFromNodeToNode(Node node1, Node node2) {
	///// VARIABLES

	Node min_node;
	float start_x, start_y; //start position of the pixel in the window coords
	float current_x, current_y; //current position of the pixel in the window coords
	int offset;
	int semiBloc = GL_SPRITE_SIZE / 2;


	///// CODE

	//Check if the nodes have the same spot
	if(node1.x == node2.x && node1.y == node2.y) {
		fprintf(stderr, "Error: both nodes have the same coords\n");
		exit(EXIT_FAILURE);
	}

	//If the nodes don't have one same coord
	if(node1.x != node2.x && node1.y != node2.y) {
		fprintf(stderr, "The nodes are not on the same horizontal/vertical line\n");
		exit(EXIT_FAILURE);
	}


	//If path is vertical
	if(node1.x == node2.x) {
		offset = abs(node1.win_y - node2.win_y) + 1 + 2*semiBloc; // +2*semiBloc beacause it is from center of the bloc to center of the other bloc

		min_node = node1; //min_node is firstly equal to node1
		//If the 'y' value of node2 is inferior to the 'y' value of min_node
		if(node2.y < min_node.y) {
			min_node = node2;
		}

		//Put the starter at the top left of the min_node sprite
		start_x = (float) min_node.win_x - semiBloc;
		start_y = (float) min_node.win_y - semiBloc;
		
		for(int i = 0; i < offset; i++) { //Each line
			for(int j = 0; j < GL_SPRITE_SIZE; j++) { //Each pixel on a line inside a bloc
				current_x = start_x + j;
				current_y = start_y + i;
				
				// DO SOMETHING BUT IT WORKS

			}
		}
	}

	//If path is horizontal
	if(node1.y == node2.y) {
		offset = abs(node1.win_x - node2.win_x) + 1 + 2*semiBloc; // +2*semiBloc beacause it is from center of the bloc to center of the other bloc

		min_node = node1; //min_node is firstly equal to node1
		//If the 'x' value of node2 is inferior to the 'x' value of min_node
		if(node2.x < min_node.x) {
			min_node = node2;
		}

		//Put the starter at the top left of the min_node sprite
		start_x = (float) min_node.win_x - semiBloc;
		start_y = (float) min_node.win_y - semiBloc;

		for(int i = 0; i < GL_SPRITE_SIZE; i++) { //Each line inside a bloc
			for(int j = 0; j < offset; j++) { //Each pixel of the lines
				current_x = start_x + j;
				current_y = start_y + i;
				printf("Hey c un test");
			}
		}
	}

	return EXIT_SUCCESS;
}
*/

long getValarcBetweenNodes(Node node1, Node node2, TowerList* tl) {
	///// VARIABLES

	Node min_node;
	float start_x, start_y; //start position of the pixel in the window coords
	float current_x, current_y; //current position of the pixel in the window coords
	int offset;
	int semiBloc = GL_SPRITE_SIZE / 2;

	int nbOfTowers = countTowers(tl);
	int counter = 0; //To fill towersArray

	long valarc = 0;

	int squareDistance = 0;


	///// CODE

	if(nbOfTowers == 0) {
		return 0;
	}

	//Check the TowerList
	Tower** towersArray = malloc(nbOfTowers*sizeof(Tower*));

	if(!towersArray) {
		fprintf(stderr, "Error: bad alloc memory for the Towers Array (valarc calculation)\n");
		exit(EXIT_FAILURE);
	}

	//Fill towersArray
	counter = 0;
	if(tl->tower) {
		towersArray[counter] = tl->tower;
		counter++;

		while(tl->nextTower) {
			tl = tl->nextTower;
			if(tl->tower) {
				towersArray[counter] = tl->tower;
				counter++;
			}
		}
	}

	//Check if counter != nbOfTowers
	if(counter != nbOfTowers) {
		fprintf(stderr, "Error : counter is different of nbOfTowers\n");
		exit(EXIT_FAILURE);
	}

	//Check if the nodes have the same spot
	if(node1.x == node2.x && node1.y == node2.y) {
		fprintf(stderr, "Error: both nodes have the same coords\n");
		exit(EXIT_FAILURE);
	}

	//If the nodes don't have one same coord
	if(node1.x != node2.x && node1.y != node2.y) {
		fprintf(stderr, "The nodes are not on the same horizontal/vertical line\n");
		exit(EXIT_FAILURE);
	}


	//If path is vertical
	if(node1.x == node2.x) {
		offset = abs(node1.win_y - node2.win_y) + 1 + 2*semiBloc; // +2*semiBloc beacause it is from center of the bloc to center of the other bloc

		min_node = node1; //min_node is firstly equal to node1
		//If the 'y' value of node2 is inferior to the 'y' value of min_node
		if(node2.y < min_node.y) {
			min_node = node2;
		}

		//Put the starter at the top left of the min_node sprite
		start_x = (float) min_node.win_x - semiBloc;
		start_y = (float) min_node.win_y - semiBloc;
		
		for(int i = 0; i < offset; i++) { //Each line
			for(int j = 0; j < GL_SPRITE_SIZE; j++) { //Each pixel on a line inside a bloc
				current_x = start_x + j;
				current_y = start_y + i;

				for(int k = 0; k < nbOfTowers; k++) {
					squareDistance = pow(current_x - towersArray[k]->win_x, 2) + pow(current_y - towersArray[k]->win_y, 2);

					if(squareDistance <= (towersArray[k]->range*towersArray[k]->range)) {
						valarc++;
					}
				}
			}
		}
	}

	//If path is horizontal
	if(node1.y == node2.y) {
		offset = abs(node1.win_x - node2.win_x) + 1 + 2*semiBloc; // +2*semiBloc beacause it is from center of the bloc to center of the other bloc

		min_node = node1; //min_node is firstly equal to node1
		//If the 'x' value of node2 is inferior to the 'x' value of min_node
		if(node2.x < min_node.x) {
			min_node = node2;
		}

		//Put the starter at the top left of the min_node sprite
		start_x = (float) min_node.win_x - semiBloc;
		start_y = (float) min_node.win_y - semiBloc;

		for(int i = 0; i < GL_SPRITE_SIZE; i++) { //Each line inside a bloc
			for(int j = 0; j < offset; j++) { //Each pixel of the lines
				current_x = start_x + j;
				current_y = start_y + i;

				for(int k = 0; k < nbOfTowers; k++) {
					squareDistance = pow(current_x - towersArray[k]->win_x, 2) + pow(current_y - towersArray[k]->win_y, 2);

					if(squareDistance <= (towersArray[k]->range*towersArray[k]->range)) {
						valarc++;
					}
				}
			}
		}
	}

	if(towersArray) {
		free(towersArray);
	}

	return valarc;
}



Node* getFirstNextNode(Node node){
	return node.link->node;
}

Node* getNextNode(Node node){
	return node.link->next->node;
}

/**************
* FUNCTIONS FOR DIJKSTRA ALGORITHM
**************/

void setInitialValuesDijkstra(Link* link) {
	if(!link) {
		return;
	}
	else {
		link->node->marqued = 0;
		//So the first node of the path is not modified via links
		if(link->node->type == 1)
			link->node->minValarc = 0;
		else
			link->node->minValarc = -1;
		setInitialValuesDijkstra(link->next);
	}
}

//Set arbitraire des valarcs dans les links en attendant de calculer les vrais valarcs
void setValarc(Node nodesArray[], int nbNodes){
	/*
	//De 0 a 1
	nodesArray[0].link->valarc = 7;
	nodesArray[1].link->valarc = 7; 
	//De 1 a 2
	nodesArray[1].link->next->valarc = 5; 
	nodesArray[2].link->valarc = 5; 
	//De 2 a 3
	nodesArray[2].link->next->valarc = 2; 
	nodesArray[3].link->valarc = 2; 
	//De 2 a 5
	nodesArray[2].link->next->next->valarc = 8; 
	nodesArray[5].link->valarc = 8; 
	//De 3 a 4
	nodesArray[3].link->next->valarc = 1; 
	nodesArray[4].link->valarc = 1;
	//De 4 a 5
	nodesArray[4].link->next->valarc = 1; 
	nodesArray[5].link->next->valarc = 1; 
	//De 5 a 6
	nodesArray[5].link->next->next->valarc = 0; 
	nodesArray[6].link->valarc = 0; 
	//De 5 a 7
	nodesArray[5].link->next->next->next->valarc = 2; 
	nodesArray[7].link->valarc = 2; 
	//De 6 a 8
	nodesArray[6].link->next->valarc = 0; 
	nodesArray[8].link->valarc = 0; 
	//De 7 a 8
	nodesArray[7].link->next->valarc = 2; 
	nodesArray[8].link->next->valarc = 2; 
	//De 8 a 9
	nodesArray[8].link->next->next->valarc = 1; 
	nodesArray[9].link->valarc = 1; 
	*/

	//De 0 a 1
	nodesArray[0].link->valarc = 2;
	nodesArray[1].link->valarc = 2; 
	//De 1 a 2
	nodesArray[1].link->next->valarc = 4; 
	nodesArray[2].link->valarc = 4; 
	//De 2 a 3
	nodesArray[2].link->next->valarc = 1; 
	nodesArray[3].link->valarc = 1; 
	//De 2 a 5
	nodesArray[2].link->next->next->valarc = 4; 
	nodesArray[5].link->valarc = 4; 
	//De 3 a 4
	nodesArray[3].link->next->valarc = 5; 
	nodesArray[4].link->valarc = 5;
	//De 4 a 5
	nodesArray[4].link->next->valarc = 2; 
	nodesArray[5].link->next->valarc = 2; 
	//De 5 a 6
	nodesArray[5].link->next->next->valarc = 0; 
	nodesArray[6].link->valarc = 0; 
	//De 5 a 7
	nodesArray[5].link->next->next->next->valarc = 1; 
	nodesArray[7].link->valarc = 1; 
	//De 6 a 8
	nodesArray[6].link->next->valarc = 3; 
	nodesArray[8].link->valarc = 3; 
	//De 7 a 8
	nodesArray[7].link->next->valarc = 0; 
	nodesArray[8].link->next->valarc = 0; 
	//De 8 a 9
	nodesArray[8].link->next->next->valarc = 2; 
	nodesArray[9].link->valarc = 2; 
	return;
}

void initializeDijkstra(Node* firstNode){
	//Setting the first node value
	firstNode->marqued = 0;
	if(firstNode->type == 1){
		firstNode->minValarc = 0;
	}else{
		firstNode->minValarc = -1;
	}
	//sets the next nodes values thanks to the links
	setInitialValuesDijkstra(firstNode->link);
}

//sets the mark of the Node to 1 when it's been visited
void markNode(Node* node){
	//printf("Marquage du noeud %d \n", node->value);
	node->marqued = 1;
}

//relache les arcs sortants
void updateNodesMinValarc(Node* originNode){
	//on recupere les infos du noeud
	int minValarcOrigin = originNode->minValarc;
	Link* link = originNode->link;
	int counter = 0;
	while(link != NULL && counter < 8){
		int newMinValarc = minValarcOrigin + link->valarc;
		//if minValarc infinite : set to min
		if (link->node->minValarc == -1 ||(link->node->minValarc > newMinValarc)){
			link->node->minValarc = newMinValarc;
			link->node->previousPath = originNode;
		}
		link = link->next;
		counter ++;
	}
	return;
}

int areAllNodesVisited(Node *nodesArray, int nbNodes){
	int counter = 0;
	int allVisited = 0; //0 means all nodes are visited
	//Stops the loop to the first encoutner of a non marked node
	while(allVisited == 0 && counter < nbNodes){
		if(nodesArray[counter].marqued == 0){
			allVisited = 1;
		}
		counter++;
	}
	return allVisited;
}

//On recherche le sommet du graphe avec le + petit minValarc qui n'a pas été parcouru
Node* getNextNodeValueWithMinValarc(Node *nodesArray, int nbNodes){
	int minValue = 15000;
	Node* tmp = NULL;
	for(int i = 0; i < nbNodes; i++){
		if(nodesArray[i].marqued == 0 && nodesArray[i].minValarc < minValue && nodesArray[i].minValarc != -1){
			tmp = &nodesArray[i];
		}
	}
	return tmp;
}

Node* pickFirstNonMarquedNode(Node *nodesArray, int nbNodes){
	int counter = 0;
	int found = 0; //when one non marqued node is found, set to 1
	Node* node = &nodesArray[0];
	while(counter < nbNodes && found == 0){
		if(nodesArray[counter].marqued == 0){
			node = &nodesArray[counter];
			printf("Value du node a parcourir : %d\n", nodesArray[counter].value);
			found = 1;
		}
		counter++;
	}
	return node;
}

//Dijkstra algorithm : sets the minValarc of each node to the minimum from the first node
void shortestPath(Node *nodesArray, int nbNodes){
	//Initialization
	for(int i =0; i < nbNodes; i++){
		initializeDijkstra(&nodesArray[i]);
	}
	Node* currentNode = &nodesArray[0];
	int allVisited = 1; //will be set to 0 when all nodes will be visited
	
	while(allVisited == 1){ // while there are still nodes to visit
		markNode(currentNode); //node gets visited : mark set to 1
		updateNodesMinValarc(currentNode); //Updating minValarc values for neighbour nodes if needed
		currentNode = getNextNodeValueWithMinValarc(nodesArray,nbNodes);
		allVisited = areAllNodesVisited(nodesArray, nbNodes); //checking if all nodes are visited
	}
	return;
}

int countNodesShortestPath(Node* nodesArray){
	//getting the end Node of the path
	Node* finalNode = &nodesArray[0];
	int found = 0;
	int counter = 0;
	while(found == 0){
		if(nodesArray[counter].type == 2){ //while it's not the end Node of the path
			finalNode = &nodesArray[counter];
			found = 1;
		}
		counter ++;
	}

	counter = 1;
	//counting the nodes
	while(finalNode->previousPath !=NULL){
		finalNode = finalNode->previousPath;
		counter ++;
	}
	return counter;
}

void fillShortestPath(int* path, int nbNodes, Node* nodesArray) {
	//getting the end Node of the path
	Node* finalNode = &nodesArray[0];
	int found = 0;
	int counter = 0;
	while(found == 0){
		if(nodesArray[counter].type == 2){ //while it's not the end Node of the path
			finalNode = &nodesArray[counter];
			found = 1;
		}
		counter ++;
	}

	for(int i = nbNodes-1; i >= 0; i--){
		path[i] = finalNode->value;
		finalNode = finalNode->previousPath;
	}
	return;
}