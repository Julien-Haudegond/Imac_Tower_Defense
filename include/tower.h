/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

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
	int type;
	int dmg;
	float firespeed;
	int range;
}Tower;

//void fire(Tower t);
Tower* createTower(Tower* tower, TowerType type);
Tower* setTowerStats(Tower* tower, int dmg, float firespeed, int range);
void printTower();

#endif