#include <stdio.h>
#include <stdlib.h>
#include "../include/tower.h"
#include "../include/wave.h"
#include "../include/window.h"
#define BASE_DMG 10
#define BASE_FIRESPEED 0.2 //Amount of shots in a unity of time : 1/10 s
#define BASE_RANGE 100 //Range in pixels

//TO DO
//void fire(Tower t);

/*Creates one tower depending on the type*/
Tower* createTower(TowerType type, int x, int y) {
	Tower* tower = malloc(sizeof(Tower));
	
	if(!tower) {
		fprintf(stderr, "Error: bad memory allocation to make a new tower\n");
		exit(EXIT_FAILURE);
	}

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

	tower->x = grid_x;
	tower->y = grid_y;
	tower->win_x = gridCoordToWindowCoord(grid_x);
	tower->win_y = gridCoordToWindowCoord(grid_y);

	switch(type){
		//Lasers : lots of dmg, fires slowly, average range
		case LASER :
			tower = setTowerStats(tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_RANGE);
			break;
		//Rockets : average dmg, fires fast, low range
		case ROCKET : 
			tower = setTowerStats(tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_RANGE*0.5));
			break;
		//Electric: low dmg, fires slowly, low range
		case ELECTRIC : 
			tower = setTowerStats(tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_RANGE*0.7));
			break;
		//Water : low dmg, fires fast, high range
		case WATER : 
			tower = setTowerStats(tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_RANGE*2));
			break;
		default : 
			printf("The type of tower you specified does not exist");
			exit(EXIT_FAILURE);
			break;
	}
	return tower;
};

Tower* setTowerStats(Tower* tower, int type, int dmg, float firespeed, int range){
	tower -> type = type;
	tower -> dmg = dmg;
	tower -> firespeed = firespeed;
	tower -> range = range;
	return tower;
}

void printTower(Tower *t){
	printf("Grid (%d,%d) / Window (%d,%d)\n", t->x, t->y, t->win_x, t->win_y);
	printf("Type: %d \n", t->type);
	printf("Damage : %d \n", t->dmg);
	printf("Firespeed : %f \n", t->firespeed);
	printf("Range : %d \n\n", t->range);
}
