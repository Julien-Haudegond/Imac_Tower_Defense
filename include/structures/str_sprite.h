#ifndef STR_SPRITE_H__
#define STR_SPRITE_H__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct Sprite {
	SDL_Surface* area;
	GLuint texture;
} Sprite;

#endif