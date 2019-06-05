#include <stdlib.h>
#include <stdio.h>

#include "nodes/link.h"

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
		printf("%ld ", link->valarc);
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


int updateAllValarcLinks(Node nodesArray[], int nbOfNodes, TowerList* tl) {
	Node current;
	Link* tmp = NULL;

	for(int i = 0; i < nbOfNodes; i++) {
		current = nodesArray[i];

		if(current.link) {
			tmp = current.link;
			tmp->valarc = getValarcBetweenNodes(current, *(tmp->node), tl);

			while(tmp->next) {
				tmp = tmp->next;
				tmp->valarc = getValarcBetweenNodes(current, *(tmp->node), tl);
			}
		}
	}

	return EXIT_SUCCESS;
}