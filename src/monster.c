#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"

Monster* createMonster(Monster* m,float health, MonsterResist resist, float speed, int playerReward){
	m->health = health;
	m->resist = resist;
	m->speed = speed;
	m->playerReward = playerReward;
	return m;
}

Monster* setPosition(Monster* m, int x, int y){
	m->x = x;
	m->y = y;
	return m;
}

void printMonster(Monster m){
	printf("%f",m.health);
}

