/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

typedef enum{
	LASER, ROCKET, ELECTRIC, WATER
}TowerType;

typedef struct Tower{
	float dmg;
	float firespeed;
	float range;
}Tower;

void fire(Tower t);


#endif