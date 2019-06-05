#ifndef STR_BUILDING_H__
#define STR_BUILDING_H__

/******************
* Types of Buildings 
*	0 Radar : better range
*	1 Factory : better damage
*	2 Ammo :  better firespeed
******************/

typedef enum { 
	RADAR, FACTORY, AMMO
} BuildingType;

typedef enum {
	RADAR_COST = 500, FACTORY_COST = 500, AMMO_COST = 500
} BuildingCost;

typedef struct Building {
	int x, y;
	int win_x, win_y;
	int type;
	int range;
	int money_cost;
} Building;

#endif