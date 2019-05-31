#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../include/tower.h"
#include "../include/monster.h"
#include "../include/building.h"
#include "../include/sprite.h"

void drawFullScreenImg(GLuint* texture);

GLuint createHelpList(GLuint help_window_texture[], Sprite sprites[]);
GLuint createPropertiesWindowList(TowerList* tl, int x, int y, GLuint properties_window_texture[]);

void drawTowerSprite(Tower* tower, Sprite sprites[]);
void drawMonsterSprite(Monster* m, Sprite sprites[], int rotation);
void drawBuildingSprite(Building* build, Sprite sprites[]);
void rotateMonsterSprite(Monster *m, int angle, Sprite sprites[]);

#endif