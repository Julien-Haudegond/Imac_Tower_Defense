#ifndef WAVE_H
#define WAVE_H
//amount of monsters for 1 wave
#define WAVESIZE 10;
#include "monster.h"

typedef struct Wave{
	Monster* monster;
	struct Wave* nextMonster;
}Wave;

void addMonster(Wave* wave, MonsterType type, int resist, int* path, int nbPath);
Wave* deleteMonster(Wave* wave);
void printWave(Wave* wave);
Wave* createEmptyWave();

#endif