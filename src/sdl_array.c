#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/sdl_array.h"

void initSurfacesArrayToNull(SDL_Surface* array[], int cst) {
	for(int i =  0; i < cst; i++) {
        array[i] = NULL;
    }
}

void initFontsArrayToNull(TTF_Font* array[], int cst) {
	for(int i =  0; i < cst; i++) {
        array[i] = NULL;
    }
}

void freeSurfacesArray(SDL_Surface* array[], int cst) {
    for(int i = 0; i < cst; i++) {
        SDL_FreeSurface(array[i]);
    }
}

void freeTexturesArray(GLuint array[], int cst) {
	for(int i = 0; i < cst; i++) {
        glDeleteTextures(1, &array[i]);
    }
}

void closeAllFonts(TTF_Font* array[], int cst) {
	for(int i = 0; i < cst; i++) {
        TTF_CloseFont(array[i]);
    }
}