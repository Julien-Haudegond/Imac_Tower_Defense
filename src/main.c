#include <stdio.h>
#include <stdlib.h>
#include "../include/monster.h"
#include "../include/wave.h"

int main(int argc, char *argv[]){
	Monster myMonster;
	Monster *ptrMyMonster = &myMonster;
	ptrMyMonster = createMonster(ptrMyMonster, 10.0, ELECTRIC, 3.0, 5);
	Wave* wave;
	wave = addMonster(wave, myMonster);
	printf("Health : %f \n", wave->monster.health);
	printf("Speed : %f \n", wave->monster.speed);
	printf("Reward : %d \n", wave->monster.playerReward);
}

