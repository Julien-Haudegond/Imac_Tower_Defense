#ifndef WAVE_H
#define WAVE_H
#include "monster.h"

typedef struct Wave{
	Monster* monster;
	struct Wave* nextMonster;
}Wave;

void addMonster(Wave* wave, MonsterType type, int resist, int* path, int nbPath);
Wave* deleteMonster(Wave* wave);
void printWave(Wave* wave);
Wave* createEmptyWave();
Wave* getLastMonster(Wave* wave);

#endif