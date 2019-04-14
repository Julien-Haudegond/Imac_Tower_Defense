#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"
#include "../include/wave.h"

/*************
*	Adds monster to the wave specified in arguments
* 	This function must be used after initializing the list containing the new monter
*************/
Wave* addMonster(Wave* wave, Monster myNewMonster){
	Wave* currentMonster = wave;
	Wave* newMonster;
	while(currentMonster != NULL && currentMonster->nextMonster != NULL){
		currentMonster = currentMonster->nextMonster;
	}
	newMonster = (Wave*)malloc(sizeof(Wave));
	if(newMonster == NULL){
		exit(EXIT_FAILURE);
	}
	newMonster -> monster = myNewMonster;
	newMonster -> nextMonster = NULL;
	if(currentMonster != NULL){
		currentMonster -> nextMonster = newMonster;
	}else{
		wave = newMonster;
	}
	return wave;
}

Wave* deleteMonster(Monster* monster, Wave* wave){
	//a remplir
	return wave;
}
