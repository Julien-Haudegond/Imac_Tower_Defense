#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"

//giants : health and resist ++ but slow
//swarmlings : fast but low health / resist
typedef enum{
	GIANT, SWARMLING
}MonsterType;

/*****
* Damages taken by monster will be divided by 2 
* Depending on resist type (cf Towers)
*****/

typedef struct Monster{
	int type;
	int *path;
	//previous node where the monster went
	int prevNode;
	//current destination node
	int currentNode;
	//nb of nodes in the path
	int nbPath;
	int x,y;
	int win_x, win_y;
	float health;
	int resist;
	int speed;
	int reward;
}Monster;

Monster* createMonster(MonsterType type, int resist, int* path, int nbPath);
void setMonsterStats(Monster* m, int type, float health, int resist, float speed, int reward, int* path, int nbPath);
void setPosition(Monster* monster, float x, float y);
void printMonster(Monster *m);
void updateCoords(Monster *m, struct Node* nodesArray, int nbNodes);
int getDirection(Monster *m, Node* nodesArray, int nbNodes);
void clipMonsterPosition(Monster* m, int direction, Node* currentNode);

#endif