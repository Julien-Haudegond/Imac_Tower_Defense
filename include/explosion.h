#ifndef EXPLOSION_H__
#define EXPLOSION_H__

typedef struct Explosion {
	int x, y;
	int win_x, win_y;
	int frame;
} Explosion;

typedef struct ExplosionList {
	struct Explosion* explosion;
	struct ExplosionList* nextExplosion;
} ExplosionList;


/***** EXPLOSION *****/
Explosion* createExplosion(int x, int y);
void printExplosion(Explosion* expl);

/***** EXPLOSION LIST *****/
ExplosionList* createEmptyExplosionList();
void freeExplosionList(ExplosionList* el);
void addExplosion(ExplosionList* el, int x, int y);
ExplosionList* deleteExplosion(ExplosionList* head);
void printExplosionList(ExplosionList* el);

/***** ANIMATION *****/
void explodeSpriteSheet(GLuint* texture, Explosion* expl);

#endif