#ifndef STR_EXPLOSION_H__
#define STR_EXPLOSION_H__

typedef struct Explosion {
	int x, y;
	int win_x, win_y;
	int frame;
} Explosion;

typedef struct ExplosionList {
	struct Explosion* explosion;
	struct ExplosionList* nextExplosion;
} ExplosionList;

#endif