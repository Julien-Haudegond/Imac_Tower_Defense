#ifndef MONSTER_H__
#define MONSTER_H__

//giants : health and resist ++ but slow
//swarmlings : fast but low health / resist
typedef enum{
	GIANTS, SWARMLINGS
}MonsterType;

/*****
* Damages taken by monster will be divided by 2 
* Depending on resist type (cf Towers)
*****/

typedef struct Monster{
	float x,y;
	float health;
	int resist;
	float speed;
	int playerReward;
}Monster;

Monster* createMonster(Monster* m, float health, int resist, float speed, int playerReward);
Monster* setPosition(Monster* monster, int x, int y);
void printMonster(Monster m);

#endif