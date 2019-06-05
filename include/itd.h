#ifndef ITD_H__
#define ITD_H__

#include "structures/str_itd.h"

#include "../include/node.h"
#include "../include/image.h"

#define NUMBER_INSTRUCT 5

int readITD(const char* fichier, Image* imgPPM, ItdColorInstruction itdInstructions[], Node nodesArray[], int* nbOfNodes);
int checkNodesDescriptions(Node nodesArray[], int* nbOfNodes, Image* imgPPM, ItdColorInstruction itdInstructions[]);
int checkPathBetween2Nodes(Node node1, Node node2, Image* imgPPM, ItdColorInstruction itdInstructions[]);
int checkAllPathsAroundANode(Node root, Image* imgPPM, ItdColorInstruction itdInstructions[]);

#endif