/*Definition of structure TowerList*/
//will be used to know which tower are on the battlefield
//Also used for buildings : each building has one list containing all the affected towers
#ifndef TOWER_LIST_H__
#define TOWER_LIST_H__


typedef struct TowerList{
	Tower tower;
	struct TowerList * nextTower;
}TowerList;


TowerList* addTower(TowerList* tl, Tower myNewTower);
TowerList* deleteTower(TowerList* tl, int x, int y);
void printTowerList(TowerList *tl);
#endif