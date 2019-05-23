#ifndef BUILDING_H__
#define BUILDING_H__

#define BASE_BUILDING_RANGE 100 //Range in pixels

#include "../include/tower_list.h"

typedef enum{
	RADAR, FACTORY, AMMO
} BuildingType;

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
} Building;

Building* createBuilding(BuildingType type, int x, int y);
void printBuilding(Building* build);

#endif