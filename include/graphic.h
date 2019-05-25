#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../include/tower.h"
#include "../include/monster.h"
#include "../include/building.h"

GLuint createHelpList(GLuint text_texture[], GLuint sprite_texture[]);

void drawTowerSprite(Tower* tower, GLuint sprite_text[]);
void drawMonsterSprite(Monster* m, GLuint sprite_text[]);
void drawBuildingSprite(Building* build, GLuint sprite_text[]);

#endif