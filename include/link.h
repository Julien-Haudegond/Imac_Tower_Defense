#ifndef LINK_H__
#define LINK_H__

#include "../include/node.h"

typedef struct Link
{
	struct Node* node;
	int distance;
	struct Link* next;
} Link;


void addLink(Link* link, struct Node* child);
void freeAllLinks(Link* link);
void printNodeLinks(Link* link);

#endif