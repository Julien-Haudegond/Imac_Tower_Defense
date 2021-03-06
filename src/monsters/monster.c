#include <stdio.h>
#include <stdlib.h>

#include "monsters/monster.h"

Monster* createMonster(MonsterType type, int resist, int* path, int nbPath){
	Monster* m = (Monster*)malloc(sizeof(Monster));
	m->path = malloc(nbPath*sizeof(int));
	switch(type){
		case GIANT:
			setMonsterStats(m, 0, 50, 50,  resist, 3, 10, path, nbPath);
			break;
		case SWARMLING:
			setMonsterStats(m, 1, 25, 25, resist, 4, 5, path, nbPath);
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

void setMonsterStats(Monster* m, int type, float health, float healthMax, int resist, float speed, int reward, int* path, int nbPath){
	m->type = type;
	m->health = health;
	m->healthMax = health;
	m->resist = resist;
	m->speed = speed;
	m->reward = reward;
	m->nbPath = nbPath;
	m->prevNode= -1;
	m->currentNode = 0;
	m->currentIndex = 0;

	for(int i = 0; i < nbPath; i++) {
		m->path[i] = path[i];
	}
}

void setInGameStats(Monster *m, float healthMax, int reward){
	m->healthMax = healthMax;
	m->health = healthMax;
	m->reward = reward;
}


void setPosition(Monster* m, float x, float y){
	if(m != NULL){
		m->win_x = x;
		m->win_y = y;
	}else{
		exit(EXIT_FAILURE);
	}
}


void updateCoords(Monster *m, Node* nodesArray, int nbNodes){
	
	//Getting previous and current node to compare coords and set monster direction
	int prevNodeValue = m->prevNode;

	int currentNodeValue = m->currentNode;
	Node* prevNode = getNodeFromValue(nodesArray, nbNodes, prevNodeValue);
	Node* currentNode = getNodeFromValue(nodesArray, nbNodes, currentNodeValue);
	//Direction : down
	
	if(prevNode->win_x == currentNode->win_x && prevNode->win_y < currentNode->win_y){
		m->win_y += m->speed ;
	}
	//Direction : up
	else if(prevNode->win_x == currentNode->win_x && prevNode->win_y > currentNode->win_y){
		m->win_y -= m->speed;
	}
	//direction : right
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x < currentNode->win_x){
		m->win_x += m->speed;
	}
	//direction : left
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x > currentNode->win_x){
		m->win_x -= m->speed;
	}
	return;
}

int getDirection(Monster *m, Node* nodesArray, int nbNodes){
	
	//Getting previous and current node to compare coords and set monster direction
	int prevNodeValue = m->prevNode;
	int currentNodeValue = m->currentNode;
	Node* prevNode = getNodeFromValue(nodesArray, nbNodes, prevNodeValue);
	Node* currentNode = getNodeFromValue(nodesArray, nbNodes, currentNodeValue);
	
	//Direction : down
	if(prevNode->win_x == currentNode->win_x && prevNode->win_y < currentNode->win_y){
		return 3;
	}
	//Direction : up
	else if(prevNode->win_x == currentNode->win_x && prevNode->win_y > currentNode->win_y){
		return 1;
	}
	//direction : right
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x < currentNode->win_x){
		return 2;
	}
	//direction : left
	else if(prevNode->win_y == currentNode->win_y && prevNode->win_x > currentNode->win_x){
		return 4;
	}
	return -1;
}


void clipMonsterPosition(Monster* m, int direction, Node* currentNode){
	if((direction == 3 && (m->win_y + m->speed) > currentNode->win_y) ||  //case direction = down & monster lower than node
		(direction == 1 && (m->win_y - m->speed) < currentNode->win_y) || //case direction = up & monster upper than node
		(direction == 2 && (m->win_x + m->speed) > currentNode->win_x) || //case direction = right & monster more right than node
		(direction == 4 && (m->win_x - m->speed) < currentNode->win_x)){  //case direction = left & monster more left than node
			m->win_x = currentNode->win_x;
			m->win_y = currentNode->win_y; 			
		}
}

int getMonsterRotation(int currentDirection){
	switch(currentDirection){
		case 1 : 
			return 180;
			break;
		case 2 :
			return -90;
			break;
		case 3 :
			return 0;
			break;
		case 4 : 
			return 90;
			break;
		default :
			return 0;
			break;
	}
}


void printMonster(Monster *m){
	printf("Health : %f \n", m->health);
	printf("Speed : %d \n", m->speed);
	printf("Reward : %d \n", m->reward);
	printf("Shortest path : ");
	for(int i = 0; i < m->nbPath; i++){
        printf("%d ",m->path[i]);
    }
    printf("\n");
}