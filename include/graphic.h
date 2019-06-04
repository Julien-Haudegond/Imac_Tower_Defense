#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../include/tower_list.h"
#include "../include/tower.h"

#include "../include/monster.h"
#include "../include/building.h"
#include "../include/building_list.h"
#include "../include/sprite.h"
#include "../include/text.h"
#include "../include/explosion.h"

void drawFullScreenImg(GLuint* texture);

GLuint createPropertiesWindowList(TowerList* tl, int x, int y, TextStyle textCSS[], Text propTowerTexts[]);

void drawTowerSprite(Tower* tower, Sprite sprites[]);
void drawMonsterSprite(Monster* m, Sprite sprites[], int rotation);
void drawBuildingSprite(Building* build, Sprite sprites[]);
void rotateMonsterSprite(Monster *m, int angle, Sprite sprites[]);
void drawHealthBar(Monster* m, Sprite sprites[]);


void globalDrawTowers(TowerList* tl, Sprite sprites[]);
void globalDrawBuildings(BuildingList* bl, Sprite sprites[]);
void globalDrawExplosions(ExplosionList* el, Sprite sprites[]);

#endif