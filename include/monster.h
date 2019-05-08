#ifndef MONSTER_H__
#define MONSTER_H__

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
	int x,y;
	int win_x, win_y;
	float health;
	int resist;
	float speed;
	int reward;
}Monster;


Monster* createMonster(Monster* m, MonsterType type, int resist);
Monster* setMonsterStats(Monster* m, int type, float health, int resist, float speed, int reward);
Monster* setPosition(Monster* monster, int x, int y);
void printMonster(Monster *m);

#endif