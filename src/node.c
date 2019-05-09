#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/node.h"
#include "../include/const.h"
#include "../include/window.h"

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
		if(node.link->valarc != NULL){
			printf("Valarcs correspondants : ");
			printValarc(node.link);
		}
	}

	printf("\n");
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

// A COMPLETER POUR AVOIR LES VALARCS !!
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


Node* getFirstNextNode(Node node){
	return node.link->node;
}

Node* getNextNode(Node node){
	return node.link->next->node;
}

//Set arbitraire des valarcs dans les links
void setValarc(Node nodesArray[], int nbNodes){
	nodesArray[0].link->valarc = 0; // de 0 a 1
	nodesArray[1].link->valarc = 0; // de 1 a 0
	nodesArray[1].link->next->valarc = 5; // de 1 a 2
	nodesArray[2].link->valarc = 5; // de 2 a 1 
	nodesArray[2].link->next->valarc = 2; // de 2 a 3
	nodesArray[3].link->valarc = 2; // de 3 a 2
	return;
}

void setInitialValuesDijkstra(Link* link) {
	if(!link) {
		return;
	}
	else {
		link->node->marqued = 0;
		link->node->minValarc = -1;
		setInitialValuesDijkstra(link->next);
	}
}

/**************
* FUNCTIONS FOR DIJKSTRA ALGORITHM
**************/

void initializeDijkstra(Node* firstNode){
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
	node->marqued = 1;
}

//Updates minValarc values according to the origin Node
void updateNodesMinValarc(Node* node){
	return;
}


//Algo dégueu qui segfault (découpage ci dessus)
/*
Node* shortestPath(Node nodesArray[], Node finalNode, int nbNodes){
   	Node currentNode = nodesArray[0];
   	Node nextNode;
   	Node nextNextNode;
   	Node tmpNode;
   	int nbNextNodes;
   	int nbVisited = 0;
   	int minValue;
   	while(currentNode.value != finalNode.value){
   		if (currentNode.type !=3){ // Node is not the end of the path
   			//Taking each next node and updating attribute minValarc
   			if(currentNode.type == 2){
   				nextNode = getNextNode(currentNode);
   				while(nextNode != NULL){
   					nextNode.minValarc = currentNode.minValarc + currentNode.link->valarc;
   					nextNode = getNextNode(nextNode);
   				}
   				nextNode = getFirstNextNode(currentNode);
   			}else if(currentNode.type == 1){
   				nextNode = getFirstNextNode(currentNode);
   				while(nextNode != NULL){
   					nextNode.minValarc = currentNode.minValarc + currentNode.link->valarc;
   					nextNode = getNextNode(nextNode);
   				}
   				nextNode = getFirstNextNode(currentNode);
   			}
   			//Selecting the nextNode with the minimum minValarc value
   			nbNextNodes = getAmountofNodes(currentNode->link);
   			minValue = nextNode.minValarc;
   			for(int j = 1; j < nbNextNodes; j++){
   				nextNode = getNextNode(nextNode);
   				if(nextNode.minValarc <= minValue){
   					minValue = nextNode.minValarc;
   					tmpNode = nextNode;
   				}
   			}
   			currentNode = tmpNode; //Next node that has minimum value minValarc		
   		}
   		
   	}
}*/
