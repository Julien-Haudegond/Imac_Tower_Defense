#ifndef STR_NODE_H__
#define STR_NODE_H__

#include "str_link.h"

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

#endif