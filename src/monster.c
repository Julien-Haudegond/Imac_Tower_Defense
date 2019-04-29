#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"

Monster* createMonster(Monster* m,float health, int resist, float speed, int playerReward){
	m = (Monster*)malloc(sizeof(Monster));
	m->health = health;
	m->resist = resist;
	m->speed = speed;
	m->playerReward = playerReward;
	return m;
}

Monster* setPosition(Monster* m, int x, int y){
	if(m != NULL){
		m->x = x;
		m->y = y;
	}else{
		exit(EXIT_FAILURE);
	}
	
	return m;
}

void printMonster(Monster *m){
	printf("Health : %f \n", m->health);
	printf("Speed : %f \n", m->speed);
	printf("Reward : %d \n", m->playerReward);
}

