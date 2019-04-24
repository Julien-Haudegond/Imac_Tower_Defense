#ifndef WAVE_H
#define WAVE_H
//amount of monsters for 1 wave
#define WAVESIZE 10;
#include "monster.h"

typedef struct Wave{
	Monster monster;
	struct Wave * nextMonster;
}Wave;

Wave* addMonster(Wave* wave, Monster myNewMonster);
Wave* deleteMonster(Wave* wave);
//Wave* deleteFirstMonster(Wave* wave);
void printWave(Wave* wave);
//void printList(Wave wave);

#endif