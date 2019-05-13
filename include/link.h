#ifndef LINK_H__
#define LINK_H__

#include "../include/node.h"
#include "../include/tower_list.h"

typedef struct Link
{
	struct Node* node;
	long valarc;
	struct Link* next;
} Link;


void addLink(Link* link, struct Node* child);
void freeAllLinks(Link* link);
void printNodeLinks(Link* link);
void printValarc(Link* link);
//Link* getNextLink(Link* link);
int getNodeValueFromLink(Link* link);

int updateAllValarcLinks(struct Node* nodesArray, int nbOfNodes, TowerList* tl);

#endif