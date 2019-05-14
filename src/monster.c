#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"

Monster* createMonster(MonsterType type, int resist, int* path, int nbPath){
	Monster* m = (Monster*)malloc(sizeof(Monster));
	m->path = malloc(nbPath*sizeof(int));
	switch(type){
		case GIANT:
			setMonsterStats(m, 0, 40, resist, 1, 30, path, nbPath);
			break;
		case SWARMLING:
			setMonsterStats(m, 1, 10, resist, 4, 5, path, nbPath);
			break;
		default : 
			exit(EXIT_FAILURE);
			break;
	}
	if(m == NULL){
		exit(EXIT_FAILURE);
	}
	
	return m;
}

void setMonsterStats(Monster* m, int type, float health, int resist, float speed, int reward, int* path, int nbPath){
	m->type = type;
	m->health = health;
	m->resist = resist;
	m->speed = speed;
	m->reward = reward;
	m->path = path;
	m->nbPath = nbPath;
}


void setPosition(Monster* m, int x, int y){
	if(m != NULL){
		m->x = x;
		m->y = y;
	}else{
		exit(EXIT_FAILURE);
	}
}

void printMonster(Monster *m){
	printf("Health : %f \n", m->health);
	printf("Speed : %f \n", m->speed);
	printf("Reward : %d \n", m->reward);
	printf("Shortest path : ");
	for(int i = 0; i < m->nbPath; i++){
        printf("%d ",m->path[i]);
    }
    printf("\n");
}

