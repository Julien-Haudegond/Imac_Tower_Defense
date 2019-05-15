//Same function than wave
#include <stdio.h>
#include <stdlib.h>
#include "../include/tower_list.h"
#include "../include/window.h"


TowerList* createEmptyTowerList() {
	TowerList* tl = malloc(sizeof(TowerList));
	tl->tower = NULL;
	tl->nextTower = NULL;

	return tl;
}

void freeTowerList(TowerList* tl) {
	if(tl) {
		if(tl->nextTower) {
			freeTowerList(tl->nextTower);
		}
		free(tl);
	}
}

/*************
*	Adds tower to the list specified in arguments
*************/
void addTower(TowerList* tl, TowerType type, int x, int y) {
	if(!tl) {
		fprintf(stderr, "Error: no tower list\n");
		exit(EXIT_FAILURE);
	}

	if(tl->tower == NULL) {
		tl->tower = createTower(type, x, y);
		return;
	}

	while(tl->nextTower != NULL) {
		tl = tl->nextTower;
	}
	
	tl->nextTower = malloc(sizeof(TowerList));
	tl = tl->nextTower;
	tl->tower = createTower(type, x, y);
	tl->nextTower = NULL;
}

/*****************
*	Delete the tower with the coordinates specified in arguments
*	From the list tl
*****************/
TowerList* deleteTower(TowerList* head, int x, int y) {
	TowerList* tmp = head;
	TowerList* prev = malloc(sizeof(TowerList));

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);


	if(tmp != NULL && tmp->tower->x == grid_x && tmp->tower->y == grid_y){
		head = tmp->nextTower;
		free(tmp);
		free(prev);
		return head;
	}

	while(tmp != NULL && (tmp->tower->x != grid_x || tmp->tower->y != grid_y)) {
		prev = tmp;
		tmp = tmp->nextTower;
	}

	if(tmp == NULL) return head;

	prev->nextTower = tmp -> nextTower;

	free(tmp);
	return head;
}

void printTowerList(TowerList* tl){

	if(!tl) {
		fprintf(stderr, "Error : no tower list\n");
		exit(EXIT_FAILURE);
	}

	int counter = 1;
	if(tl->tower != NULL){
		// a optimiser
		while(tl->nextTower != NULL){
			printf("Tower %d \n", counter);
			printTower(tl->tower);
			tl = tl->nextTower;
			counter++;
		}
		if(tl->nextTower == NULL){
		//printing last tower
			printf("Tower %d \n", counter);
			printTower(tl->tower);
			//tl = tl->nextTower;
		}
	}
	if(tl->tower == NULL && tl->nextTower == NULL) {
		printf("Tower list is empty.\n");
	}
}

int countTowers(TowerList* tl) {
	int counter = 0;

	if(tl->tower == NULL && tl->nextTower == NULL) {
		return 0;
	}

	if(tl->tower) {
		counter++;
		while(tl->nextTower) {
			tl = tl->nextTower;
			if(tl->tower) {
				counter++;				
			}
		}
	}

	return counter;
}