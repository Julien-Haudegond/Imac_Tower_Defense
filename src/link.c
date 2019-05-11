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
void setNextLinkMinValarc(Link* link){
	printf("Valeur de la marque en %d - getNextNode : %d \n",link->node->value, link->node->marqued);
	printf("Valeur de la marque en %d - getNextNode : %d \n",link->next->node->value, link->next->node->marqued);
	if(link->node != NULL && link->next !=NULL){
		int min = 15000;
		Link* minLink; // noeud 0
		//printf("Adresse de link %d \n",link);
		while(link != NULL && link->next != NULL){
			if(link->node->marqued == 0 && link->valarc < min){
				printf("Noeud %d non marqué !\n", link->node->value);
				min = link->valarc;
				minLink = link;
			}

			link = link->next;
			
		}
		printf("Noeud suivant le + petit valarc : %d \n",link->node->value);
		link = minLink;
	}
}

