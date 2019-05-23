#include <stdio.h>
#include <stdlib.h>

#include "../include/building_list.h"
#include "../include/window.h"

BuildingList* createEmptyBuildingList() {
	BuildingList* bl = malloc(sizeof(BuildingList));
	bl->build = NULL;
	bl->nextBuild = NULL;

	return bl;
}

void freeBuildingList(BuildingList* bl) {
	if(bl) {
		if(bl->build) {
			free(bl->build);
		}
		if(bl->nextBuild) {
			freeBuildingList(bl->nextBuild);
		}
		free(bl);
	}
}


/*************
*	Add buildings to the list specified in arguments
*************/
void addBuilding(BuildingList* bl, BuildingType type, int x, int y) {
	if(!bl) {
		fprintf(stderr, "Error: no building list\n");
		exit(EXIT_FAILURE);
	}

	if(bl->build == NULL) {
		bl->build = createBuilding(type, x, y);
		return;
	}

	while(bl->nextBuild != NULL) {
		bl = bl->nextBuild;
	}
	
	bl->nextBuild = malloc(sizeof(BuildingList));
	bl = bl->nextBuild;
	bl->build = createBuilding(type, x, y);
	bl->nextBuild = NULL;
}

BuildingList* deleteBuilding(BuildingList* head, int x, int y) {
	if(!head) {
		fprintf(stderr, "Error : no building list (deleteBuilding)\n");
		exit(EXIT_FAILURE);
	}

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

	BuildingList* tmp = head;
	BuildingList* prev = head;

    //If the list is empty
    if(tmp->build == NULL && tmp->nextBuild == NULL) {
    	return tmp;
    }

    //If only one building in the list and we delete it
    if((tmp->build->x == grid_x && tmp->build->y == grid_y) && tmp->nextBuild == NULL) {
    	free(tmp->build);
    	tmp->build = NULL;
    	tmp->nextBuild = NULL;

    	return tmp;
    }

    //If the first one is the good building to delete but there are several buildings in the list
	if(tmp->build != NULL && tmp->nextBuild != NULL && tmp->build->x == grid_x && tmp->build->y == grid_y) {
		head = tmp->nextBuild;
		free(tmp->build);
		free(tmp);

		return head;
	}

	while(tmp) {
		if(tmp->build) {
			if(tmp->build->x == grid_x && tmp->build->y == grid_y) {
				prev->nextBuild = tmp->nextBuild;
				free(tmp->build);
				free(tmp);

				break;
			}
			else {
				prev = tmp;
				tmp = tmp->nextBuild;			
			}
		}
	}

	return head;
}

void printBuildingList(BuildingList* bl) {
	if(!bl) {
		fprintf(stderr, "Error : no building list\n");
		exit(EXIT_FAILURE);
	}

	int counter = 1;
	if(bl->build != NULL){
		// a optimiser
		while(bl->nextBuild != NULL){
			printf("Building %d \n", counter);
			printBuilding(bl->build);
			bl = bl->nextBuild;
			counter++;
		}
		if(bl->nextBuild == NULL){
		//printing last building
			printf("Building %d \n", counter);
			printBuilding(bl->build);
		}
	}
	if(bl->build == NULL && bl->nextBuild == NULL) {
		printf("Building list is empty.\n");
	}
}

int countBuildings(BuildingList* bl) {
	int counter = 0;

	if(bl->build == NULL && bl->nextBuild == NULL) {
		return 0;
	}

	if(bl->build) {
		counter++;
		while(bl->nextBuild) {
			bl = bl->nextBuild;
			if(bl->build) {
				counter++;				
			}
		}
	}

	return counter;
}