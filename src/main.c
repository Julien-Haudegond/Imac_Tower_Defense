#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"
#include "../include/wave.h"

int main(int argc, char *argv[]){
	//creating first monster
	Monster myMonster;
	Monster *ptrMyMonster = &myMonster;
	ptrMyMonster = createMonster(ptrMyMonster, 10.0, ELECTRIC, 3.0, 18);
	//creating 2nd monster
	Monster myMonster2;
	Monster *ptrMyMonster2 = &myMonster2;
	ptrMyMonster2 = createMonster(ptrMyMonster2, 2.0, ELECTRIC, 4.0, 22);
	//creating 3rd monster
	Monster myMonster3;
	Monster *ptrMyMonster3 = &myMonster3;
	ptrMyMonster3 = createMonster(ptrMyMonster3, 42.0, ELECTRIC, 42.0, 42);
	//adding monsters to the wave
	//Monster are now considered as wave elements
	Wave* wave;
	wave = addMonster(wave, myMonster);
	wave = addMonster(wave, myMonster2);
	wave = addMonster(wave, myMonster3);
	printWave(wave);
	//1st monster gets killed 
	printf("Changing monster health \n");
	Monster* ptrWaveElem = &(wave->monster);
	ptrWaveElem = setHealth(ptrWaveElem, 0);
	printMonster(wave->monster);
	wave = deleteFirstMonster(wave);
	printf("First Monster removed !\n");
	printWave(wave);
}

