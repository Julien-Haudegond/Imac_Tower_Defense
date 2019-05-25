#ifndef MAP_DRAW_H__
#define MAP_DRAW_H__

#include "../include/image.h"
#include "../include/itd.h"
#include "../include/node.h"
#include "../include/tower.h"
#include "../include/building.h"


void drawGridSquare(int filled);
void drawWindowSquare(int filled);
void drawFullScreen(uint r, uint g, uint b, uint a);
void drawPropertiesScreen(uint r, uint g, uint b, uint a);


//DEBUG DRAW
GLuint debugDrawIDList(Image* imgPPM);
GLuint debugDrawNodesIDList(Node nodesArray[], int* nbOfNodes);
void debug_constructibleArea();
void debug_pathArea();
void debug_nodeArea();
void debug_startArea();
void debug_endArea();

//DRAW MAP
GLuint createMapIDList(Image* imgPPM, ItdColorInstruction itdInstructions[], GLuint sprite_text[]);
void nonConstructibleArea();


//CHECK MAP EVOLUTION
void availableArea(int mouse_x, int mouse_y, GLuint sprite_text[]);
void nonAvailableArea(int mouse_x, int mouse_y, GLuint sprite_text[]);

int isItAvailableArea(int x, int y, Image* ppm, ItdColorInstruction itdInstructions[], TowerList* tl, BuildingList* bl);
int constructionGuides(int x, int y, Image* ppm, ItdColorInstruction itdInstructions[], GLuint sprite_text[], TowerList* tl, BuildingList* bl);

void drawTowerGuides(int mouse_x, int mouse_y, TowerType type, GLuint sprite_text[]);
void drawBuildingGuides(int mouse_x, int mouse_y, BuildingType type, GLuint sprite_text[]);

#endif