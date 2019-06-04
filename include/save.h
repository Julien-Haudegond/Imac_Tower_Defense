#ifndef SAVE_H__
#define SAVE_H__

#define MAX_TOWERS_BUILDINGS 100

#include "../include/tower_list.h"
#include "../include/building_list.h"

int saveGame(const char* itdPath, int money, int wave, TowerList* tl, BuildingList* bl, int status);
int pathSavedGame(char* itdPath);
int loadSavedGame(int* money, int* wave, TowerList* tl, BuildingList* bl);
int deleteSavedData();

int isThereASave();

#endif