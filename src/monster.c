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
	m->nbPath = nbPath;
	m->prevNode= -1;
	m->currentNode = 0;

	for(int i = 0; i < nbPath; i++) {
		m->path[i] = path[i];
	}
}


void setPosition(Monster* m, float x, float y){
	if(m != NULL){
		m->win_x = x;
		m->win_y = y;
	}else{
		exit(EXIT_FAILURE);
	}
}

//int getMonsterDirection(Monster* m,)
void updateCoords(Monster *m, Node* nodesArray, int nbNodes){
	
	
	//Getting previous and current node to compare coords and set monster direction
	int prevNodeValue = m->prevNode;

	int currentNodeValue = m->currentNode;
	Node* prevNode = getNodeFromValue(nodesArray, nbNodes, prevNodeValue);
	Node* currentNode = getNodeFromValue(nodesArray, nbNodes, currentNodeValue);
	//Direction : down
	
	if(prevNode->win_x == currentNode->win_x && prevNode->win_y < currentNode->win_y){
		m->win_y ++;
	}
	//Direction : up
	else if(prevNode->win_x == currentNode->win_x && prevNode->win_y > currentNode->win_y){
		m->win_y --;
	}
	//direction : right
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x < currentNode->win_x){
		m->win_x ++;
	}
	//direction : left
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x > currentNode->win_x){
		m->win_x --;
	}
	return;
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

