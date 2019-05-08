#include <stdio.h>
#include <stdlib.h>
#include "../include/building.h"

Building* createBuilding(Building* bd, TowerType type){
	tower = (Tower*)malloc(sizeof(Tower));
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
	if(tower == NULL){
		exit(EXIT_FAILURE);
	}
	return tower;
};