#ifndef BUILDING_LIST_H__
#define BUILDING_LIST_H__

#include "../structures/str_building_list.h"

#include "../constructions/building.h"

BuildingList* createEmptyBuildingList();
void freeBuildingList(BuildingList* bl);

void addBuilding(BuildingList* bl, BuildingType type, int x, int y);
BuildingList* deleteBuilding(BuildingList* head, int x, int y, int* global_money);
void printBuildingList(BuildingList* bl);
int countBuildings(BuildingList* bl);

#endif