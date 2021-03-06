/*Definition of structure TowerList*/
//will be used to know which tower are on the battlefield
//Also used for buildings : each building has one list containing all the affected towers
#ifndef TOWER_LIST_H__
#define TOWER_LIST_H__

#include "../structures/str_tower_list.h"

#include "../constructions/tower.h"
#include "../constructions/building_list.h"
#include "../constructions/building.h"


TowerList* createEmptyTowerList();
void freeTowerList(TowerList* tl);


void addTower(TowerList* tl, TowerType type, int x, int y);
TowerList* deleteTower(TowerList* head, int x, int y, int* global_money);
void printTowerList(TowerList *tl);
int countTowers(TowerList* tl);

int isThereTowerHere(TowerList* tl, int x, int y);
void getTowerInfosFromPosition(Tower** t, TowerList* tl, int x, int y);

int getSquareDistanceTowerBuilding(Tower* t, Building* b);
void updateTowersBuildings(TowerList* tl, BuildingList* bl);


#endif