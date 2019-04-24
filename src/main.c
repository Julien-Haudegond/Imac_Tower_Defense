#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/monster.h"
#include "../include/wave.h"
#include "../include/tower.h"

#include "../include/itd.h"
#include "../include/node.h"
#include "../include/image.h"
//#define DONTREADTHISCODE 0

int main(int argc, char** argv) 
{
	Image imgPPM;
	ItdColorInstruction itdInstructions[NUMBER_INSTRUCT] = {0};
	Node nodesArray[MAX_NODES] = {0};
	int nbOfNodes;

    readITD("images/Map_01.itd", &imgPPM, itdInstructions, nodesArray, &nbOfNodes);

    //Printf the five instructions' values
	for(int i = 0; i < NUMBER_INSTRUCT; i++) {
		printf("%s : %d %d %d\n", itdInstructions[i].name, itdInstructions[i].r, itdInstructions[i].g, itdInstructions[i].b);
	}

    printf("Nombre de noeuds : %d\n", nbOfNodes);

    for(int i = 0; i < nbOfNodes; i++) {
    	printNodeInfo(nodesArray[i]);
    }

    //Faut free les linkkkksss et l'image
    for(int i = 0; i < nbOfNodes; i++) {
    	freeAllLinks(nodesArray[i].link);
    }
    freeImage(&imgPPM);

   return EXIT_SUCCESS;
}

#ifdef DONTREADTHISCODE

void TestMonsters2(){
    Monster myMonster;
    Monster *ptrMyMonster = &myMonster;
    ptrMyMonster = createMonster(ptrMyMonster, 10.0, 0, 3.0, 18);

    Monster myMonster2;
    Monster *ptrMyMonster2 = &myMonster2;
    ptrMyMonster2 = createMonster(ptrMyMonster2, 2.0, 0, 4.0, 22);

    Wave* wave = addMonster(wave, myMonster);
    wave = addMonster(wave, myMonster2);

    wave->nextMonster->monster.health = 0;

    printWave(wave);
    wave = deleteMonster(wave);
    wave = deleteMonster(wave);
    printWave(wave);
    
}

void TestTower(){
    Tower* t = createTower(t, WATER);
    printTower(t);
}
//Main pour tests
int main(){
    TestMonsters2();
    return 0;
}



#endif