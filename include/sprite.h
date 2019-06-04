#ifndef SPRITE_H__
#define SPRITE_H__

#define MAX_SPRITES 30

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct Sprite {
	SDL_Surface* area;
	GLuint texture;
} Sprite;

//Sprites array
void initSpritesToNull(Sprite sprites[]);
void fillSprites(Sprite sprites[]);

void freeSprites(Sprite sprites[]);

//One sprite
int loadSpriteArea(SDL_Surface** image, const char* fichier);
int initSpriteTexture(SDL_Surface** image, GLuint* texture);

void drawSprite(GLuint* texture);
void drawSpriteHere(GLuint* texture, int x, int y);

#endif