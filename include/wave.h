#ifndef WAVE_H
#define WAVE_H
//amount of monsters for 1 wave
#define WAVESIZE 10;
#include "monster.h"

typedef struct Wave Wave;
struct Wave{
	Monster monster;
	Wave * nextMonster;
};

Wave* addMonster(Wave* wave, Monster myNewMonster);
Wave* deleteMonster(Monster* monster, Wave* wave);
//void printList(Wave wave);

#endif