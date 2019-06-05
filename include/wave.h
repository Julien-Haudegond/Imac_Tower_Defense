#ifndef WAVE_H
#define WAVE_H

#include "structures/str_wave.h"

#include "monster.h"

void addMonster(Wave* wave, MonsterType type, int resist, int* path, int nbPath);
Wave* deleteMonster(Wave* wave);
void printWave(Wave* wave);
Wave* createEmptyWave();
Wave* getLastMonster(Wave* wave);

#endif