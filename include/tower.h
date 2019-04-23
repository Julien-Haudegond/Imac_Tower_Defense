/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

typedef enum{
	LASER, ROCKET, ELECTRIC, WATER
}TowerType;

typedef struct Tower{
	int dmg;
	float firespeed;
	int range;
}Tower;

//void fire(Tower t);
Tower* createTower(Tower* tower, TowerType type);
Tower* setTowerStats(Tower* tower, int dmg, float firespeed, int range);
void printTower();

#endif