#ifndef NODE_H__
#define NODE_H__

#include "../include/link.h"

#define MAX_NODES 20 //Max number of nodes will be 20-1 = 19

typedef enum {
	IN = 1, OUT = 2, BEND = 3, INTERSECT = 4
} NodeType;

typedef struct Node {
	int value;
	int type;
	int x, y; //Grid coords
	int win_x, win_y; //Window coords
	int marqued;
	struct Link* link;
} Node;


Node createNode(int value, int type, int x, int y);
void linkNode(Node* root, Node* child);
void printNodeInfo(Node node);
int doInAndOutExist(Node nodesArray[], int* nbOfNodes);
int isTherePathFromINtoOUT(Node nodesArray[], int* nbOfNodes);
int depthFirstSearchFromRoot(Node nodesArray[], int* nbOfNodes, Node* root);
int deleteAllMarksOnNodes(Node nodesArray[], int* nbOfNodes);
int travelPathFromNodeToNode(Node node1, Node node2);
Node* getFirstNextNode(Node node);
Node* getNextNode(Node node);
//Node* shortestPath(Node nodesArray[], Node finalNode, int nbNodes)

#endif