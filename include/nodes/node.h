#ifndef NODE_H__
#define NODE_H__

#include "../structures/str_node.h"

#include "../constructions/tower_list.h"

#include "../nodes/link.h"

#define MAX_NODES 25 //Max number of nodes will be 25

//Create / get info from Nodes
Node createNode(int value, int type, int x, int y);
void linkNode(Node* root, Node* child);
void printNodeInfo(Node node);

//Checking Nodes functions
int doInAndOutExist(Node nodesArray[], int* nbOfNodes);
int isTherePathFromINtoOUT(Node nodesArray[], int* nbOfNodes);
int depthFirstSearchFromRoot(Node nodesArray[], int* nbOfNodes, Node* root);
int deleteAllMarksOnNodes(Node nodesArray[], int* nbOfNodes);
//int travelPathFromNodeToNode(Node node1, Node node2);

long getValarcBetweenNodes(Node node1, Node node2, TowerList* tl);

//Getters
Node* getFirstNextNode(Node node);
Node* getNextNode(Node node);
Node* getNodeFromValue(Node *nodesArray, int nbNodes, int value);

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