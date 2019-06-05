/*Definition of structures for Towers*/
#ifndef TOWER_H__
#define TOWER_H__

#include "../structures/str_tower.h"

#include "../monsters/monster.h"

#define BASE_DMG 10
#define BASE_FIRESPEED 0.2 //Amount of shots in a unity of time : 1/10 s
#define BASE_TOWER_RANGE 100 //Range in pixels


//void fire(Tower t);
int checkTowerMoney(TowerType type, int money_cost);
Tower* createTower(TowerType type, int x, int y);
Tower* setTowerStats(Tower* tower, int type, int dmg, float firespeed, int range);
void printTower(Tower *t);
int isMonsterInTheRange(Tower* t, Monster* m);
void fire(Tower* t, Monster* m);

#endif