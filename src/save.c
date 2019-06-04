#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/save.h"


int saveGame(const char* itdPath, int money, int wave, TowerList* tl, BuildingList* bl, int status) {
	const char* fichier = "data/save.txt";

	//Open a file
	FILE* F = fopen(fichier,"w");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	//if the player did not finish the game
	if(status != 0 && status != 1) {

		fprintf(F,"# MAP\n");
		fprintf(F, "%s\n", itdPath);

		fprintf(F,"# MONEY\n");
		fprintf(F, "%d\n", money);

		fprintf(F,"# WAVE\n");
		fprintf(F, "%d\n", wave);

		fprintf(F,"# TOWERS & BUILDINGS\n");
	    if(tl->tower) {
	        TowerList* tmp = tl;
	        fprintf(F, "%d %d %d %d\n", 1, tmp->tower->type, tmp->tower->win_x, tmp->tower->win_y);

	        while(tmp->nextTower) {
	            tmp = tmp->nextTower;
	            if(tmp->tower) {
	                fprintf(F, "%d %d %d %d\n", 1, tmp->tower->type, tmp->tower->win_x, tmp->tower->win_y);
	            }
	        }
	    }
	    if(bl->build) {
	        BuildingList* tmp = bl;
	        fprintf(F, "%d %d %d %d\n", 2, tmp->build->type, tmp->build->win_x, tmp->build->win_y);

	        while(tmp->nextBuild) {
	            tmp = tmp->nextBuild;
	            if(tmp->build) {
	                fprintf(F, "%d %d %d %d\n", 2, tmp->build->type, tmp->build->win_x, tmp->build->win_y);
	            }
	        }
	    }
	}

	//else, the file is overwrite with empty data.

	fclose(F);
	return EXIT_SUCCESS;
}

int pathSavedGame(char* itdPath) {
	const char* fichier = "data/save.txt";
	int reader;

	//If there is no saved game
	if(isThereASave() == 0) {
		return EXIT_SUCCESS;
	}

	//Open a file
	FILE* F = fopen(fichier,"r");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments : # MAP
		reader = getc(F);
		//If the first character is a #, it reads the whole line and go to the next one
		while (reader == '#'){
			while(getc(F) != '\n');
			reader = getc(F);
		}
		ungetc(reader, F);

	if(fscanf(F, "%s\n", itdPath) != 1) {
		fprintf(stderr, "Error during reading the save file\n");
		exit(EXIT_FAILURE);
	}

	fclose(F);
	return EXIT_SUCCESS;
}


int loadSavedGame(int* money, int* wave, TowerList* tl, BuildingList* bl) {
	///// VARIABLES
	const char* fichier = "data/save.txt";
	int reader;
	char map[30];

	//Last lines
	int k = 0; //Iterator for line number
	char line[80] = {0}; //Used to read the lines
	char delim[2] = " "; //Character which separate the integers in the string (here, a space)
	char *token; //Pointer to the first character after a delimiter character (here, a space)
	int values[MAX_TOWERS_BUILDINGS][4] = {0}; //Temporary integers' array used to stock the read values : [1st] is the line number / [2nd] is the integer number inside the line (maximun 4 HERE)
	int nbIntegers = 0;


	///// CODE

	//If there is no saved game
	if(isThereASave() == 0) {
		return EXIT_SUCCESS;
	}

	//Open a file
	FILE* F = fopen(fichier,"r");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments : # MAP
		reader = getc(F);
		//If the first character is a #, it reads the whole line and go to the next one
		while (reader == '#'){
			while(getc(F) != '\n');
			reader = getc(F);
		}
		ungetc(reader, F);

	if(fscanf(F, "%s\n", map) != 1) {
		fprintf(stderr, "Error during reading the save file\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments : # MONEY
		reader = getc(F);
		//If the first character is a #, it reads the whole line and go to the next one
		while (reader == '#'){
			while(getc(F) != '\n');
			reader = getc(F);
		}
		ungetc(reader, F);

	if(fscanf(F, "%d\n", money) != 1) {
		fprintf(stderr, "Error during reading the save file\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments : # WAVE
		reader = getc(F);
		//If the first character is a #, it reads the whole line and go to the next one
		while (reader == '#'){
			while(getc(F) != '\n');
			reader = getc(F);
		}
		ungetc(reader, F);

	if(fscanf(F, "%d\n", wave) != 1) {
		fprintf(stderr, "Error during reading the save file\n");
		exit(EXIT_FAILURE);
	}

	//Skip comments : # TOWERS & BUILDINGS
		reader = getc(F);
		//If the first character is a #, it reads the whole line and go to the next one
		while (reader == '#'){
			while(getc(F) != '\n');
			reader = getc(F);
		}
		ungetc(reader, F);

	//Read towers & building lines
	k = 0;
	//Read a line in the file and stock the content in the string 'line'
	while(fgets(line, 80, F) != NULL) { 
		token = strtok(line, delim); 
		while(token != NULL) {
			values[k][nbIntegers] = atoi(token); //Fill the array with the read values for the line 'k' with the position of the current integer
			token = strtok(NULL, delim);
			nbIntegers++;
		}
		nbIntegers = 0;
		k++;
	}
			/*
			for(int i = 0; i < k; i++) {
				for(int z = 0; z < 4; z++) {
					printf("%d ", values[i][z]);
				}	
				printf("\n");
			}
			*/

	//We travel each line of the array 'values'
	//values[][0] = tower OR building (1 OR 2)
	//values[][1] = construction type (0,1, 2 OR 3)
	//values[][2] = Position x
	//values[][3] = Position Y
	for(int i = 0; i < MAX_TOWERS_BUILDINGS; i++) {
		if(values[i][0] == 1) {
			addTower(tl, values[i][1], values[i][2], values[i][3]);
		}
		else if(values[i][0] == 2) {
			addBuilding(bl, values[i][1], values[i][2], values[i][3]);
		}
		else {
			break;
		}
	}

	fclose(F);
	return EXIT_SUCCESS;
}

//Return 1 if yes, 0 if not
int isThereASave() {
	const char* fichier = "data/save.txt";

	//Open a file
	FILE* F = fopen(fichier,"r");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	long fsize = 0;

	fseek(F, 0, SEEK_END);
	fsize = ftell(F);

	if(fsize == 0) {
		fclose(F);
		return 0;
	}

	fclose(F);
	return 1;
}


int deleteSavedData() {
	const char* fichier = "data/save.txt";

	//Open a file
	FILE* F = fopen(fichier,"w");
	if (!F){
		fprintf(stderr, "Unable to open the file.\n");
		exit(EXIT_FAILURE);
	}

	fclose(F);
	return EXIT_SUCCESS;
}