#ifndef STR_LINK_H__
#define STR_LINK_H__

#include "str_node.h"

typedef struct Link
{
	struct Node* node;
	long valarc;
	struct Link* next;
} Link;

#endif