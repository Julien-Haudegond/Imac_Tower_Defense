#ifndef NODE_H__
#define NODE_H__

#include "../include/link.h"

#define MAX_NODES 20 //Max number of nodes will be 20-1 = 19

typedef enum {
	IN, OUT, INTERSECT, BEND
} NodeType;

typedef struct Node {
	int value;
	int type;
	int x;
	int y;
	struct Link* link;
} Node;


Node createNode(int value, int type, int x, int y);
void linkNode(Node* root, Node* child);
void printNodeInfo(Node node);
int doInAndOutExist(Node nodesArray[], int* nbOfNodes);

#endif