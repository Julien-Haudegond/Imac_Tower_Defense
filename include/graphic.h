#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../include/tower.h"

GLuint createHelpList(GLuint text_texture[]);

void drawTowerSprite(Tower* tower, GLuint sprite_text[]);

#endif