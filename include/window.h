#ifndef WINDOW_H__
#define WINDOW_H__

#include <SDL/SDL.h>

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int gridCoordToWindowCoord(int grid_coord);
int windowCoordToGridCoord(int win_coord);
int windowCoordToBlocCenter(int win_coord);

#endif