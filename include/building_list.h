#ifndef BUILDING_LIST_H__
#define BUILDING_LIST_H__

#include "../include/building.h"

typedef struct BuildingList {
	struct Building* build;
	struct BuildingList * nextBuild;
} BuildingList;

BuildingList* createEmptyBuildingList();
void freeBuildingList(BuildingList* bl);

void addBuilding(BuildingList* bl, BuildingType type, int x, int y);
BuildingList* deleteBuilding(BuildingList* head, int x, int y);
void printBuildingList(BuildingList* bl);
int countBuildings(BuildingList* bl);

#endif