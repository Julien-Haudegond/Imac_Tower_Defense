/*Definition of structure TowerList*/
//will be used to know which tower are on the battlefield
//Also used for buildings : each building has one list containing all the affected towers
#ifndef STR_TOWER_LIST_H__
#define STR_TOWER_LIST_H__

#include "str_tower.h"


typedef struct TowerList{
	Tower* tower;
	struct TowerList * nextTower;
}TowerList;


#endif