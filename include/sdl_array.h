#ifndef FREE_H__
#define FREE_H__

void initSurfacesArrayToNull(SDL_Surface* array[], int cst);
void initFontsArrayToNull(TTF_Font* array[], int cst);

void freeSurfacesArray(SDL_Surface* array[], int cst);
void freeTexturesArray(GLuint array[], int cst);
void closeAllFonts(TTF_Font* array[], int cst);

#endif