#ifndef BUILDING_H__
#define BUILDING_H__

#define BASE_BUILDING_RANGE 100 //Range in pixels

#include "structures/str_building.h"

int checkBuildingMoney(BuildingType type, int money_cost);
Building* createBuilding(BuildingType type, int x, int y);
void printBuilding(Building* build);

#endif