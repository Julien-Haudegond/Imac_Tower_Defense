#include <stdlib.h>
#include <stdio.h>

#include "../include/node.h"

Node createNode(int value, int type, int x, int y) {
	Node node;

	node.value = value;
	node.type = type;
	node.x = x;
	node.y = y;

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
	printf("Noeud %d, type %d, position(%d,%d). ", node.value, node.type, node.x, node.y);
	if(node.marqued == 1) {
		printf("Le noeud est marqué. ");
	}
	else if(node.marqued == 0) {
		printf("Le noeud n'est pas marqué. ");
	}

	if(node.link != NULL) {
		printf("Il est relié à : ");
		printNodeLinks(node.link);
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