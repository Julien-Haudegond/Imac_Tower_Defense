#ifndef MAP_DRAW_H__
#define MAP_DRAW_H__

#include "../include/image.h"

void drawSquare(int filled);

GLuint createMapIDList(Image* imgPPM);
void constructibleArea();
void pathArea();
void nodeArea();
void startArea();
void endArea();

#endif