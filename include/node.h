#ifndef NODE_H__
#define NODE_H__

#include "../include/link.h"

#define MAX_NODES 20 //Max number of nodes will be 20-1 = 19

typedef enum {
	IN = 1, OUT = 2, BEND = 3, INTERSECT = 4
} NodeType;

typedef struct Node {
	int minValarc;
	struct Node* previousPath; //Previous node for shortest path
	int value;
	int type;
	int x, y; //Grid coords
	int win_x, win_y; //Window coords
	int marqued;
	struct Link* link;
} Node;

//Create / get info from Nodes
Node createNode(int value, int type, int x, int y);
void linkNode(Node* root, Node* child);
void printNodeInfo(Node node);

//Checking Nodes functions
int doInAndOutExist(Node nodesArray[], int* nbOfNodes);
int isTherePathFromINtoOUT(Node nodesArray[], int* nbOfNodes);
int depthFirstSearchFromRoot(Node nodesArray[], int* nbOfNodes, Node* root);
int deleteAllMarksOnNodes(Node nodesArray[], int* nbOfNodes);
int travelPathFromNodeToNode(Node node1, Node node2);

//Getters for next nodes
Node* getFirstNextNode(Node node);
Node* getNextNode(Node node);

//Functions for Dijkstra
int areAllNodesVisited(Node *nodesArray, int nbNodes);
void initializeDijkstra(Node* firstNode);
void setValarc(Node nodesArray[], int nbNodes);
void markNode(Node* node);
void updateNodesMinValarc(Node* node);
void setInitialValuesDijkstra(struct Link* link);
Node* pickFirstNonMarquedNode(Node *nodesArray, int nbNodes);
//struct Link* setNextLinkMinValarc(struct Link* link);
void shortestPath(Node *nodesArray, int nbNodes);
int countNodesShortestPath(Node* nodesArray);
void fillShortestPath(int* path, int nbNodes, Node* nodesArray);

#endif