/*Definition of structures for Towers*/
#ifndef STR_TOWER_H__
#define STR_TOWER_H__

typedef enum {
	LASER, ROCKET, ELECTRIC, WATER
} TowerType;

typedef enum {
	LASER_COST = 500, ROCKET_COST = 500, ELECTRIC_COST = 500, WATER_COST = 500
} TowerCost;

/******************
* Types of towers
*		0 : Laser
*		1 : Rocket
*		2 : Electric
*		3 : Water
* Will later be compared to monsters resist
*/

typedef struct Tower {
	int x,y;
	int win_x, win_y;
	int type;
	int dmg;
	int firespeed;
	int range;
	int money_cost;
} Tower;


#endif