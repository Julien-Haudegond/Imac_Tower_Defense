#ifndef EXPLOSION_H__
#define EXPLOSION_H__

#include "../structures/str_explosion.h"

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