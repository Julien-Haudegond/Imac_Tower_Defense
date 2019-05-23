/*Definition of structure TowerList*/
//will be used to know which tower are on the battlefield
//Also used for buildings : each building has one list containing all the affected towers
#ifndef TOWER_LIST_H__
#define TOWER_LIST_H__

#include "../include/tower.h"

typedef struct TowerList{
	Tower* tower;
	struct TowerList * nextTower;
}TowerList;


TowerList* createEmptyTowerList();
void freeTowerList(TowerList* tl);


void addTower(TowerList* tl, TowerType type, int x, int y);
TowerList* deleteTower(TowerList* head, int x, int y);
void printTowerList(TowerList *tl);
int countTowers(TowerList* tl);

#endif