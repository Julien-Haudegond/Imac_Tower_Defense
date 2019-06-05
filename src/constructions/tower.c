#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constructions/tower.h"

#include "gui/window.h"

//Check money for tower construct (0 is not OK, everything else is price)
int checkTowerMoney(TowerType type, int money_cost) {
	switch(type) {
		case LASER:
			if(money_cost >= LASER_COST) return LASER_COST;
			break;
		case ROCKET:
			if(money_cost >= ROCKET_COST) return ROCKET_COST;
			break;
		case ELECTRIC:
			if(money_cost >= ELECTRIC_COST) return ELECTRIC_COST;
			break;
		case WATER:
			if(money_cost >= WATER_COST) return WATER_COST;
			break;

		default:
			break;
	}

	return 0;
}

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
			tower = setTowerStats(tower, 0, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_TOWER_RANGE);
			tower->money_cost = LASER_COST;
			break;
		//Rockets : average dmg, fires fast, low range
		case ROCKET : 
			tower = setTowerStats(tower, 1, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_TOWER_RANGE*0.5));
			tower->money_cost = ROCKET_COST;
			break;
		//Electric: low dmg, fires slowly, low range
		case ELECTRIC : 
			tower = setTowerStats(tower, 2, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_TOWER_RANGE*0.7));
			tower->money_cost = ELECTRIC_COST;
			break;
		//Water : low dmg, fires fast, high range
		case WATER : 
			tower = setTowerStats(tower, 3, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_TOWER_RANGE*2));
			tower->money_cost = WATER_COST;
			break;
		default : 
			printf("The type of tower you specified does not exist");
			exit(EXIT_FAILURE);
			break;
	}
	return tower;
};

Tower* setTowerStats(Tower* tower, int type, int dmg, float firespeed, int range){
	tower->type = type;
	tower->dmg = dmg;
	tower->firespeed = firespeed;
	tower->range = range;
	return tower;
}

void printTower(Tower *t){
	printf("Grid (%d,%d) / Window (%d,%d)\n", t->x, t->y, t->win_x, t->win_y);
	printf("Type: %d \n", t->type);
	printf("Damage : %d \n", t->dmg);
	printf("Firespeed : %f \n", t->firespeed);
	printf("Range : %d \n", t->range);
	printf("Cost: %d $ \n\n", t->money_cost);
}


/*
int isMonsterInTheRange(Tower* t, Monster* m){
	float distance = sqrt(pow(t->win_x - m->win_x,2)+pow(t->win_y - m->win_y,2));
	printf("Distance : %f", distance);
	if(distance <= t->range){
		return 1;
	}
	return 0;
}

void fire(Tower* t, Monster *m){
	int monsterInRange = isMonsterInTheRange(t,m);
}

*/
