#ifndef MAP_DRAW_H__
#define MAP_DRAW_H__

#include "../include/image.h"
#include "../include/itd.h"

void drawSquare(int filled);


//DEBUG DRAW
GLuint debugDrawIDList(Image* imgPPM);
void debug_constructibleArea();
void debug_pathArea();
void debug_nodeArea();
void debug_startArea();
void debug_endArea();

//DRAW MAP
GLuint createMapIDList(Image* imgPPM, ItdColorInstruction itdInstructions[]);
void constructibleArea();
void pathArea();
void nonConstructibleArea();


#endif