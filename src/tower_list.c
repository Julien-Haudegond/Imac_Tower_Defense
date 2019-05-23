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
		if(tl->tower) {
			free(tl->tower);
		}
		if(tl->nextTower) {
			freeTowerList(tl->nextTower);
		}
		free(tl);
	}
}

/*************
*	Add tower to the list specified in arguments
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
	if(!head) {
		fprintf(stderr, "Error : no tower list (deleteTower)\n");
		exit(EXIT_FAILURE);
	}

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

	TowerList* tmp = head;
	TowerList* prev = head;

    //If the list is empty
    if(tmp->tower == NULL && tmp->nextTower == NULL) {
    	return tmp;
    }

    //If only one tower in the list and we delete it
    if((tmp->tower->x == grid_x && tmp->tower->y == grid_y) && tmp->nextTower == NULL) {
    	free(tmp->tower);
    	tmp->tower = NULL;
    	tmp->nextTower = NULL;

    	return tmp;
    }

    //If the first one is the good tower to delete but there are several towers in the list
	if(tmp->tower != NULL && tmp->nextTower != NULL && tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
		head = tmp->nextTower;
		free(tmp->tower);
		free(tmp);

		return head;
	}

	while(tmp) {
		if(tmp->tower) {
			if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
				prev->nextTower = tmp->nextTower;
				free(tmp->tower);
				free(tmp);

				break;
			}
			else {
				prev = tmp;
				tmp = tmp->nextTower;			
			}
		}
	}

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