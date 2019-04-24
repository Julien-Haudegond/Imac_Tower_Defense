#include <stdio.h>
#include <stdlib.h>
#include "../include/tower.h"
#include "../include/wave.h"
#define BASE_DMG 10
#define BASE_FIRESPEED 0.2 //Amount of shots in a unity of time : 1/10 s
#define BASE_RANGE 100 //Range in pixels

//TO DO
//void fire(Tower t);

/*Creates one tower depending on the type)*/
Tower* createTower(Tower* tower, TowerType type){
	tower = (Tower*)malloc(sizeof(Tower));
	switch(type){
		//Lasers : lots of dmg, fires slowly, average range
		case LASER :
			tower = setTowerStats(tower, (int)(BASE_DMG*1.5), BASE_FIRESPEED*0.7, BASE_RANGE);
			break;
		//Rockets : average dmg, fires fast, low range
		case ROCKET : 
			tower = setTowerStats(tower, BASE_DMG, BASE_FIRESPEED*1.8, (int)(BASE_RANGE*0.5));
			break;
		//Electric: low dmg, fires slowly, low range
		case ELECTRIC : 
			tower = setTowerStats(tower, (int)(BASE_DMG*0.7), BASE_FIRESPEED*0.7, (int)(BASE_RANGE*0.7));
			break;
		//Water : low dmg, fires fast, high range
		case WATER : 
			tower = setTowerStats(tower, (int)(BASE_DMG*0.6), BASE_FIRESPEED*1.7, (int)(BASE_RANGE*2));
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

Tower* setTowerStats(Tower* tower, int dmg, float firespeed, int range){
	tower -> dmg = dmg;
	tower -> firespeed = firespeed;
	tower -> range = range;
	return tower;
}

void printTower(Tower *t){
	printf("Type: %d \n", t->type);
	printf("Damage : %d \n", t->dmg);
	printf("Firespeed : %f \n", t->firespeed);
	printf("Range : %d \n", t->range);
}
