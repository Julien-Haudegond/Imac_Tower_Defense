#ifndef STR_WAVE_H
#define STR_WAVE_H

#include "str_monster.h"

typedef struct Wave{
	Monster* monster;
	struct Wave* nextMonster;
}Wave;


#endif