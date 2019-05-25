#ifndef BUILDING_H__
#define BUILDING_H__

#define BASE_BUILDING_RANGE 100 //Range in pixels

typedef enum { 
	RADAR, FACTORY, AMMO
} BuildingType;

typedef enum {
	RADAR_COST = 500, FACTORY_COST = 500, AMMO_COST = 500
} BuildingCost;

/******************
* Types of Buildings 
*	0 Radar : better range
*	1 Factory : better damage
*	2 Ammo :  better firespeed
******************/

typedef struct Building {
	int x, y;
	int win_x, win_y;
	int type;
	int range;
	int money_cost;
} Building;

int checkBuildingMoney(BuildingType type, int money_cost);
Building* createBuilding(BuildingType type, int x, int y);
void printBuilding(Building* build);

#endif