#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../include/tower.h"
#include "../include/monster.h"
#include "../include/building.h"
#include "../include/sprite.h"
#include "../include/text.h"

void drawFullScreenImg(GLuint* texture);

GLuint createHelpList(TextStyle textCSS[], Text helpTexts[], Sprite sprites[]);
GLuint createPropertiesWindowList(TowerList* tl, int x, int y, TextStyle textCSS[], Text propTowerTexts[]);

void drawTowerSprite(Tower* tower, Sprite sprites[]);
void drawMonsterSprite(Monster* m, Sprite sprites[], int rotation);
void drawBuildingSprite(Building* build, Sprite sprites[]);
void rotateMonsterSprite(Monster *m, int angle, Sprite sprites[]);

#endif