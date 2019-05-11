//Same function than wave
#include <stdio.h>
#include <stdlib.h>
#include "../include/tower.h"
#include "../include/tower_list.h"

/*************
*	Adds tower to the list specified in arguments
*************/
TowerList* addTower(TowerList* tl, Tower myNewTower){
	TowerList* currentTower = tl;
	TowerList* newTowerNode;
	if(currentTower != NULL && currentTower->nextTower != NULL){
		currentTower = currentTower->nextTower;
	}
	newTowerNode = (TowerList*)malloc(sizeof(TowerList));
	if(newTowerNode == NULL){
		exit(EXIT_FAILURE);
	}
	newTowerNode -> tower = myNewTower;
	newTowerNode -> nextTower = NULL;
	if(currentTower != NULL){
		currentTower -> nextTower = newTowerNode;
	}else{
		tl = newTowerNode;
	}
	return tl;
}

/*****************
*	Delete the tower with the coordinates specified in arguments
*	From the list tl
*****************/
TowerList* deleteTower(TowerList* head, int x, int y){
	TowerList* tmp = head;
	TowerList* prev = malloc(sizeof(TowerList));
	if(tmp != NULL && tmp->tower.x == x && tmp->tower.y == y){
		head = tmp->nextTower;
		free(tmp);
		return head;
	}

	while(tmp != NULL && tmp->tower.x  != x && tmp->tower.y != y){
		prev = tmp;
		tmp = tmp->nextTower;
	}

	if(tmp == NULL) return head;

	prev->nextTower = tmp -> nextTower;

	free(tmp);
	return head;
}

void printTowerList(TowerList* tl){
	int counter = 1;
	if(tl != NULL){
		// a optimiser
		while(tl->nextTower != NULL){
			printf("Tower %d \n", counter);
			printTower(&(tl->tower));
			tl = tl->nextTower;
			counter++;
		}
		if(tl->nextTower == NULL){
		//printing last monster
			printf("Tower %d \n", counter);
			printTower(&(tl->tower));
			tl = tl->nextTower;
		}
	}
}