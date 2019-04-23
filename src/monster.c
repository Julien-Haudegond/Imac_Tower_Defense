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

Monster* setHealth(Monster *m, int newHealth){
	m->health = newHealth;
	return m;
}

void printMonster(Monster m){
	printf("Health : %f \n", m.health);
	printf("Speed : %f \n", m.speed);
	printf("Reward : %d \n", m.playerReward);
}

