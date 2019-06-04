/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

//#include "../include/monster.h"

#define BASE_DMG 10
#define BASE_FIRESPEED 0.2 //Amount of shots in a unity of time : 1/10 s
#define BASE_TOWER_RANGE 100 //Range in pixels

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
	float firespeed;
	int range;
	int money_cost;
} Tower;


//void fire(Tower t);
int checkTowerMoney(TowerType type, int money_cost);
Tower* createTower(TowerType type, int x, int y);
Tower* setTowerStats(Tower* tower, int type, int dmg, float firespeed, int range);
void printTower(Tower *t);
//int isMonsterInTheRange(Tower* t, Monster* m);
//void fire(Tower* t, Monster* m);

#endif