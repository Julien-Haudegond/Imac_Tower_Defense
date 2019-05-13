/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

#define MAX_TOWERS 20

typedef enum{
	LASER, ROCKET, ELECTRIC, WATER
}TowerType;

/******************
* Types of towers
*		0 : Laser
*		1 : Rocket,
*		2 : Electric
*		3 : Water
* Will later be compared to monsters resist
*/
typedef struct Tower{
	int x,y;
	int win_x, win_y;
	int type;
	int dmg;
	float firespeed;
	int range;
}Tower;


//void fire(Tower t);
Tower* createTower(TowerType type, int x, int y);
Tower* setTowerStats(Tower* tower, int type, int dmg, float firespeed, int range);
void printTower(Tower *t);

#endif