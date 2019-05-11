#ifndef LINK_H__
#define LINK_H__

#include "../include/node.h"

typedef struct Link
{
	struct Node* node;
	int valarc;
	struct Link* next;
} Link;


void addLink(Link* link, struct Node* child);
void freeAllLinks(Link* link);
void printNodeLinks(Link* link);
void printValarc(Link* link);
//Link* getNextLink(Link* link);
int getNodeValueFromLink(Link* link);
void setNextLinkMinValarc(Link* link);

#endif