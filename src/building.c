#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/building.h"
#include "../include/window.h"

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

	build->range = BASE_BUILDING_RANGE;

	return build;
}

void printBuilding(Building* build) {
	printf("Position: grid(%d,%d) / window(%d,%d)\n", build->x, build->y, build->win_x, build->win_y);
	printf("Range: %d\n", build->range);
	printf("Type: %d\n", build->type);
}