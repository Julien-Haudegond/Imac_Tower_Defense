#include <stdio.h>
#include <stdlib.h>

#include "monsters/monster.h"
#include "monsters/wave.h"

Wave* createEmptyWave() {
	Wave* wave = malloc(sizeof(Wave));
	wave->monster = NULL;
	wave->nextMonster = NULL;

	return wave;
}

void freeWave(Wave* wave) {
	if(wave) {
		if(wave->monster) {
			free(wave->monster);
		}
		if(wave->nextMonster) {
			freeWave(wave->nextMonster);
		}
		free(wave);
	}
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

	if(!head) {
		fprintf(stderr, "Error : no wave (deleteMonster)\n");
		exit(EXIT_FAILURE);
	}

	Wave* tmp = head;
	Wave* prev = malloc(sizeof(Wave));

	//if wave is empty
	if(tmp != NULL && tmp->monster == NULL && tmp->nextMonster == NULL) {
		return tmp;
	}
	
	//If the first Monster of the list is dead, delete and replace it by the next one (if not null)
	if(tmp != NULL && tmp->monster != NULL && tmp->monster->health <= 0 && tmp->nextMonster != NULL){
		//printf("pas null\n");
		head = tmp->nextMonster;
		free(tmp->monster->path);
		free(tmp->monster);
		free(tmp);
		free(prev);
		return head;

	//Only monster in the wave	
	}else if(tmp != NULL && tmp->monster != NULL && tmp->monster->health <= 0 && tmp->nextMonster==NULL){
		//printf("Ca passe \n");
		
		free(tmp->monster->path);
		free(tmp->monster);
		tmp->monster = NULL;
		tmp->nextMonster = NULL;

		free(prev);
		return tmp; 
	}
	//printf("Ca passe 2\n");
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

Wave* getLastMonster(Wave* wave){
	while (wave->nextMonster != NULL){
		wave = wave->nextMonster;
	}
	Wave* current = wave;
	return current;
}

void printWave(Wave* wave){
	int counter = 1;
	if(!wave) {
		fprintf(stderr, "Error: no wave\n");
		exit(EXIT_FAILURE);
	}

	if(wave->monster != NULL){
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
			//wave = wave->nextMonster;
		}
	}

	if(wave->monster == NULL && wave->nextMonster == NULL) {
		printf("Wave is empty.\n");
	}
}
	
