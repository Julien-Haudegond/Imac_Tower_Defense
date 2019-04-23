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