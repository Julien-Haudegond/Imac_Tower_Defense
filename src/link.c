#include <stdlib.h>
#include <stdio.h>

#include "../include/link.h"

void addLink(Link* link, Node* child) {
	if(link->next == NULL) {
		link->next = malloc(sizeof(Link));

		if(!link->next) {
			fprintf(stderr, "Bad allocation memory for link.\n");
			exit(EXIT_FAILURE);
		}

		link->next->node = child;
		link->next->next = NULL;
	}
	else addLink(link->next, child);
}

void freeAllLinks(Link* link) {
	if(link) {
		freeAllLinks(link->next);
		free(link);
	}
}


void printNodeLinks(Link* link) {
	if(!link) {
		return;
	}
	else {
		printf("%d ", link->node->value);
		printNodeLinks(link->next);
	}
}

void printValarc(Link* link) {
	if(!link) {
		return;
	}
	else {
		printf("%d ", link->valarc);
		printValarc(link->next);
	}
}
/*
Link* getNextLink(Link* link){
	if(!link || !link->next){
		return;
	}
	return link->next;
}*/

int getNodeValueFromLink(Link* link){
	return link->node->value;
}

//Maybe check the type of node before ? 
Node* getNextNodesMinValarc(Link* link){
	if(link->node != NULL){
		int min = 15000;
		Node* minNode = link->node;
		printf("Adresse de link %d \n",link);
		while(link != NULL && link->next != NULL){
			if(link->node->marqued != 1 && link->node->value < min){
				min = link->next->node->value;
				minNode = link->node;
			}
			link = link->next;
		}
		return minNode;
	}
}



