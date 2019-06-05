#ifndef STR_TEXT_H__
#define STR_TEXT_H__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_ttf.h>

typedef struct TextStyle {
	TTF_Font* font;
	SDL_Color color;
} TextStyle;

typedef struct Text {
	SDL_Surface* area;
	GLuint texture;
} Text;

#endif