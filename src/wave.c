#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"
#include "../include/wave.h"


Wave* createEmptyWave() {
	Wave* wave = malloc(sizeof(Wave));
	wave->monster = NULL;
	wave->nextMonster = NULL;

	return wave;
}

/*************
*	Adds monster to the wave specified in arguments
* 	This function must be used after initializing the list containing the new monter
*************/
void addMonster(Wave* wave, MonsterType type, int resist, int* path, int nbPath){
	if(!wave){
		fprintf(stderr, "Error: no wave\n");
		exit(EXIT_FAILURE);
	}

	//empty wave : setting first element
	if(wave->monster == NULL){
		wave->monster = createMonster(type, resist, path, nbPath);
		return;
	}

	//parsing wave until finding a non NULL element
	while(wave->nextMonster != NULL){
		wave = wave->nextMonster;
	}

	wave->nextMonster = malloc(sizeof(Wave));
	wave = wave->nextMonster;
	wave->monster = createMonster(type, resist, path, nbPath);
	wave->nextMonster = NULL;
}

//a optimiser ou à appeler en boucle tant que tous les monstres dead ne sont pas éliminés
Wave* deleteMonster(Wave* head){

	Wave* tmp = head;
	Wave* prev = malloc(sizeof(Wave));
	


	//If the first Monster of the list is dead, delete and replace it by the next one (if not null)
	if(tmp != NULL && tmp->monster != NULL && tmp->monster->health <= 0 && tmp->nextMonster != NULL){
		printf("pas null");
		head = tmp->nextMonster;
		free(tmp->monster->path);
		free(tmp->monster);
		free(tmp);
		free(prev);
		return head;


	//Only monster in the wave	
	}else if(tmp != NULL && tmp->monster != NULL && tmp->monster->health <= 0 && tmp->nextMonster==NULL){
		printf("Ca passe \n");
		
		free(tmp->monster->path);
		free(tmp->monster);
		free(tmp);
		free(prev);
		return tmp; // segfault here
	}
	printf("Ca passe 2");
	while(tmp != NULL && tmp->monster !=NULL && tmp->monster->health > 0){
		prev = tmp;
		tmp = tmp->nextMonster;
	}

	if(tmp == NULL) return head;

	if (prev != NULL){		
		prev->nextMonster = tmp->nextMonster;
		free(tmp->monster->path);
		free(tmp->monster);
		free(tmp);
	}
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
	
