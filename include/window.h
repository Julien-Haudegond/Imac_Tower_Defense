#ifndef WINDOW_H__
#define WINDOW_H__

#include "../include/const.h"

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);
int gridCoordToWindowCoord(int grid_coord);

#endif