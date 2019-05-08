#ifndef BUILDING_H__
#define BUILDING_H__

/******************
* Types of Buildings 
*	0 Radar : better range
*	1 Factory : better damage
*	2 Ammo :  better firespeed
******************/
typedef struct Building{
	int x,y;
	int win_x, win_y;
	int type;
	int range;
	//each building has a list of towers on which it's active
	struct TowerList* firstTower;
}Building;

Building* createBuilding(Building* bd, int type);

#endif