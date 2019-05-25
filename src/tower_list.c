//Same function than wave
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
TowerList* deleteTower(TowerList* head, int x, int y, int* global_money) {
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
    	*global_money += (int) tmp->tower->money_cost / 2;
    	free(tmp->tower);
    	tmp->tower = NULL;
    	tmp->nextTower = NULL;

    	return tmp;
    }

    //If the first one is the good tower to delete but there are several towers in the list
	if(tmp->tower != NULL && tmp->nextTower != NULL && tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
		head = tmp->nextTower;
		*global_money += (int) tmp->tower->money_cost / 2;
		free(tmp->tower);
		free(tmp);

		return head;
	}

	while(tmp) {
		if(tmp->tower) {
			if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
				prev->nextTower = tmp->nextTower;
				*global_money += (int) tmp->tower->money_cost / 2;
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
	printf("\n");
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

// 0 if no tower, 1 if tower
int isThereTowerHere(TowerList* tl, int x, int y) {
    if(!tl) {
        fprintf(stderr, "Error : no tower list (isThereTowerHere)\n");
        exit(EXIT_FAILURE);
    }

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

    if(tl->tower) {
        TowerList* tmp = tl;
        if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) return 1;

        while(tmp->nextTower) {
            tmp = tmp->nextTower;
            if(tmp->tower) {
                if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) return 1;
            }
        }
    }

    return 0;
}

void getTowerInfosFromPosition(Tower** t, TowerList* tl, int x, int y) {
    if(!tl) {
        fprintf(stderr, "Error : no tower list (getTowerFromPosition)\n");
        exit(EXIT_FAILURE);
    }

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);


    if(tl->tower) {
        TowerList* tmp = tl;
        if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
        	(*t)->x = tmp->tower->x;
        	(*t)->y = tmp->tower->y;
        	(*t)->range = tmp->tower->range;
        	(*t)->dmg = tmp->tower->dmg;
        	(*t)->firespeed = tmp->tower->firespeed;
        	return;
        }

        while(tmp->nextTower) {
            tmp = tmp->nextTower;
            if(tmp->tower) {
                if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) {
			        (*t)->x = tmp->tower->x;
		        	(*t)->y = tmp->tower->y;
		        	(*t)->range = tmp->tower->range;
		        	(*t)->dmg = tmp->tower->dmg;
		        	(*t)->firespeed = tmp->tower->firespeed;
	                return; 	
                } 
            }
        }
    }
}


/*************************************************************/

int getSquareDistanceTowerBuilding(Tower* t, Building* b) {
	int squareDistance = 0;

	squareDistance = pow((t->win_x - b->win_x), 2) + pow((t->win_y - b->win_y), 2);

	return squareDistance;
}


void updateTowersBuildings(TowerList* tl, BuildingList* bl) {
	if(!tl) {
		fprintf(stderr, "Error : no tower list (updateTowersBuildings).\n");
		exit(EXIT_FAILURE);
	}
	if(!bl) {
		fprintf(stderr, "Error : no building list (updateTowersBuildings).\n");
		exit(EXIT_FAILURE);
	}

	//Get all the buildings
		int index = 0;
		int nbOfBuildings = countBuildings(bl);

		//If no building : reset all parameters of towerList
		if(nbOfBuildings == 0) {
			if(tl->tower) {
		    	TowerList* tmp = tl;
		    		//Reset all the parameters of the towers
		    		switch(tmp->tower->type){
						case LASER :
							tmp->tower = setTowerStats(tmp->tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_TOWER_RANGE);
							break;
						case ROCKET : 
							tmp->tower = setTowerStats(tmp->tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_TOWER_RANGE*0.5));
							break;
						case ELECTRIC : 
							tmp->tower = setTowerStats(tmp->tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_TOWER_RANGE*0.7));
							break;
						case WATER : 
							tmp->tower = setTowerStats(tmp->tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_TOWER_RANGE*2));
							break;
					}

		    	while(tmp->nextTower) {
		    		tmp = tmp->nextTower;
		    		if(tmp->tower) {
			    		//Reset all the parameters of the towers
			    		switch(tmp->tower->type){
							case LASER :
								tmp->tower = setTowerStats(tmp->tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_TOWER_RANGE);
								break;
							case ROCKET : 
								tmp->tower = setTowerStats(tmp->tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_TOWER_RANGE*0.5));
								break;
							case ELECTRIC : 
								tmp->tower = setTowerStats(tmp->tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_TOWER_RANGE*0.7));
								break;
							case WATER : 
								tmp->tower = setTowerStats(tmp->tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_TOWER_RANGE*2));
								break;
						}    			
		    		}
		    	}
		    }
			return;
		}

		Building** buildingArray = malloc(nbOfBuildings*sizeof(Building)); //Temporary dynamic array which contains all the buildings

		if(!buildingArray) {
			fprintf(stderr, "Error: bad alloc memory for the Towers Array (valarc calculation)\n");
			exit(EXIT_FAILURE);
		}

		//Fill the array
	    if(bl->build) {
	        BuildingList* tmp = bl;
	        buildingArray[index] = tmp->build;
	        index++;

	        while(tmp->nextBuild) {
	            tmp = tmp->nextBuild;
	            if(tmp->build) {
	                buildingArray[index] = tmp->build;
	        		index++;
	            }
	        }
	    }

	    if(index != nbOfBuildings) {
	    	fprintf(stderr, "Error : problem with the number of buildings (updateTowersBuildings).\n");
	    	exit(EXIT_FAILURE);
	    }


    //Make the updates for each tower
	    if(tl->tower) {
	    	TowerList* tmp = tl;
	    		//Reset all the parameters of the towers
	    		switch(tmp->tower->type){
					case LASER :
						tmp->tower = setTowerStats(tmp->tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_TOWER_RANGE);
						break;
					case ROCKET : 
						tmp->tower = setTowerStats(tmp->tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_TOWER_RANGE*0.5));
						break;
					case ELECTRIC : 
						tmp->tower = setTowerStats(tmp->tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_TOWER_RANGE*0.7));
						break;
					case WATER : 
						tmp->tower = setTowerStats(tmp->tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_TOWER_RANGE*2));
						break;
				}

		    	//Check each building effect
		    	for(int i = 0; i < nbOfBuildings; i++) {
		    		if(getSquareDistanceTowerBuilding(tmp->tower, buildingArray[i]) < pow(buildingArray[i]->range, 2)) {
		    			switch(buildingArray[i]->type) {
		    				case RADAR: //Increase range by 25%
		    					tmp->tower->range = (int) tmp->tower->range * 1.25;
		    					break;
		    				case FACTORY: //Increase damage by 25%
		    					tmp->tower->dmg = (int) tmp->tower->dmg * 1.25;
		    					break;
		    				case AMMO: //Increase firespeed by 25%
		    					tmp->tower->firespeed = tmp->tower->firespeed * 1.25;
		    					break;
		    			}
		    		}
		    	}

	    	while(tmp->nextTower) {
	    		tmp = tmp->nextTower;
	    		if(tmp->tower) {
		    		//Reset all the parameters of the towers
		    		switch(tmp->tower->type){
						case LASER :
							tmp->tower = setTowerStats(tmp->tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_TOWER_RANGE);
							break;
						case ROCKET : 
							tmp->tower = setTowerStats(tmp->tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_TOWER_RANGE*0.5));
							break;
						case ELECTRIC : 
							tmp->tower = setTowerStats(tmp->tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_TOWER_RANGE*0.7));
							break;
						case WATER : 
							tmp->tower = setTowerStats(tmp->tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_TOWER_RANGE*2));
							break;
					}
			    	//Check each building effect
			    	for(int i = 0; i < nbOfBuildings; i++) {
			    		if(getSquareDistanceTowerBuilding(tmp->tower, buildingArray[i]) < pow(buildingArray[i]->range, 2)) {
			    			switch(buildingArray[i]->type) {
			    				case RADAR: //Increase range by 25%
			    					tmp->tower->range = (int) tmp->tower->range * 1.25;
			    					break;
			    				case FACTORY: //Increase damage by 25%
			    					tmp->tower->dmg = (int) tmp->tower->dmg * 1.25;
			    					break;
			    				case AMMO: //Increase firespeed by 25%
			    					tmp->tower->firespeed = tmp->tower->firespeed * 1.25;
			    					break;
			    			}
			    		}
			    	}	    			
	    		}
	    	}
	    }

    free(buildingArray);
}