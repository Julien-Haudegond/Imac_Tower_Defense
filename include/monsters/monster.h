#ifndef MONSTER_H__
#define MONSTER_H__

#include "../structures/str_monster.h"

#include "../nodes/node.h"

Monster* createMonster(MonsterType type, int resist, int* path, int nbPath);
void setMonsterStats(Monster* m, int type, float health, float healthMax, int resist, float speed, int reward, int* path, int nbPath);
void setInGameStats(Monster *m, float healthMax, int reward);
void setPosition(Monster* monster, float x, float y);
void updateCoords(Monster *m, struct Node* nodesArray, int nbNodes);
int getDirection(Monster *m, Node* nodesArray, int nbNodes);
int monsterNeedsClipping(Monster* m, int direction, Node* currentNode);
void clipMonsterPosition(Monster* m, int direction, Node* currentNode);
int getMonsterRotation(int currentDirection);
void printMonster(Monster *m);

#endif