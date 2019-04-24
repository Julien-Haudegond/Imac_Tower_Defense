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

//deletes one element
//a optimiser ou à appeler en boucle tant que tous les monstres dead ne sont pas éliminés
Wave* deleteMonster(Wave* head){
	Wave* tmp = head;
	Wave* prev;
	//If the first Monster of the list is dead, delete and replace it by the next one 
	if(tmp != NULL && tmp->monster.health <= 0){
		head = tmp->nextMonster;
		free(tmp);
		return head;
	}

	while(tmp != NULL && tmp->monster.health > 0){
		prev = tmp;
		tmp = tmp->nextMonster;
	}

	if(tmp == NULL) return head;


	prev->nextMonster = tmp -> nextMonster;
	free(tmp);
	return head;
}

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
	
