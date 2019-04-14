#ifndef MONSTER_H__
#define MONSTER_H__

//giants : health and resist ++ but slow
//swarmlings : fast but low health / resist
typedef enum{
	GIANTS, SWARMLINGS
}MonsterType;

typedef enum{
	LASER, ROCKET, ELECTRIC, WATER
}MonsterResist;

typedef struct Monster{
	float x,y;
	float health;
	MonsterResist resist;
	float speed;
	int playerReward;
}Monster;

Monster* createMonster(Monster* m, float health, MonsterResist resist, float speed, int playerReward);
Monster* setPosition(Monster* monster, int x, int y);
Monster* setHealth(Monster *m, int newHealth);
void printMonster(Monster m);

#endif