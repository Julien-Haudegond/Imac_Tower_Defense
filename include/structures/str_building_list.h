#ifndef STR_BUILDING_LIST_H__
#define STR_BUILDING_LIST_H__

#include "str_building.h"

typedef struct BuildingList {
	struct Building* build;
	struct BuildingList * nextBuild;
} BuildingList;

#endif