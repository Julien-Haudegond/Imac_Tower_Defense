#ifndef STR_MONSTER_H__
#define STR_MONSTER_H__


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
	int currentIndex;
	//nb of nodes in the path
	int nbPath;
	int x,y;
	int win_x, win_y;
	float health;
	float healthMax;
	int resist;
	int speed;
	int reward;
}Monster;


#endif