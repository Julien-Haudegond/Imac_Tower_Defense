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
//Removes monster having health <= 0 from the list
Wave* deleteMonster(Wave* wave){
	if(wave == NULL){
		exit(EXIT_FAILURE);
	}
	//removing first element of the list if necessary
	if(wave->monster.health <=0){
		printf("Monster health <=0 \n");
		wave = deleteFirstMonster(wave);
	}
	while(wave->nextMonster != NULL){
		if(wave->nextMonster->monster.health <= 0){
			//tmp is the new pointer value for the previous element
			Wave* tmp = wave->nextMonster->nextMonster;
			wave->nextMonster->nextMonster = NULL;
			free(wave->nextMonster);
			wave->nextMonster = tmp;
		}
		wave = wave->nextMonster;
	}
	return wave;
}

Wave* deleteFirstMonster(Wave* wave){
	printf("Deleting first monster \n");
	Wave *tmp;
	tmp = wave->nextMonster;
	free(wave);
	return tmp;
}
/*
Wave* deleteLastMonster(Wave* wave){
	return wave;
}*/

void printWave(Wave* wave){
	int counter = 1;
	if(wave != NULL){
		// a optimiser
		while(wave->nextMonster != NULL){
			printf("Monster %d \n", counter);
			printMonster(wave->monster);
			wave = wave->nextMonster;
			counter++;
		}
		//printing last monster
		if(wave->nextMonster == NULL){
			printf("Monster %d \n", counter);
			printMonster(wave->monster);
			wave = wave->nextMonster;
		}
	}
}
	
