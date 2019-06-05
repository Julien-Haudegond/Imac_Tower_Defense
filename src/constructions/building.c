#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "constructions/building.h"

#include "gui/window.h"


//Check money for building construct (0 is not OK, everything else is price)
int checkBuildingMoney(BuildingType type, int money_cost) {
	switch(type) {
		case RADAR:
			if(money_cost >= RADAR_COST) return RADAR_COST;
			break;
		case FACTORY:
			if(money_cost >= FACTORY_COST) return FACTORY_COST;
			break;
		case AMMO:
			if(money_cost >= AMMO_COST) return AMMO_COST;
			break;

		default:
			break;
	}

	return 0;
}

Building* createBuilding(BuildingType type, int x, int y) {
	Building* build = malloc(sizeof(Building));

	if(!build) {
		fprintf(stderr, "Error: bad memory allocation to make a new building.\n");
		exit(EXIT_FAILURE);
	}

	if(type != RADAR && type != FACTORY && type != AMMO) {
		fprintf(stderr, "Error: this type of building doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

	build->x = grid_x;
	build->y = grid_y;
	build->win_x = gridCoordToWindowCoord(grid_x);
	build->win_y = gridCoordToWindowCoord(grid_y);

	build->type = type;

	switch(type) {
		case RADAR:
			build->money_cost = RADAR_COST;
			break;
		case FACTORY:
			build->money_cost = FACTORY_COST;
			break;
		case AMMO:
			build->money_cost = AMMO_COST;
			break;

		default:
			break;
	}

	build->range = BASE_BUILDING_RANGE;

	return build;
}

void printBuilding(Building* build) {
	printf("Position: grid(%d,%d) / window(%d,%d)\n", build->x, build->y, build->win_x, build->win_y);
	printf("Range: %d\n", build->range);
	printf("Type: %d\n", build->type);
	printf("Cost: %d $\n\n", build->money_cost);
}