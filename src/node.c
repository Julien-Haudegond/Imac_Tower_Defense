#include <stdlib.h>
#include <stdio.h>

#include "../include/node.h"

Node createNode(int value, int type, int x, int y) {
	Node node;

	node.value = value;
	node.type = type;
	node.x = x;
	node.y = y;

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
	if(node.link != NULL) {
		printf("Il est relié à : ");
		printNodeLinks(node.link);
	}
	printf("\n");
}