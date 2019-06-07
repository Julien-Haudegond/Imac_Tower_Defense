#ifndef GRAPHIC_H__
#define GRAPHIC_H__

#include "../animations/explosion.h"

#include "../constructions/tower_list.h"
#include "../constructions/tower.h"
#include "../constructions/building.h"
#include "../constructions/building_list.h"

#include "../gui/sprite.h"
#include "../gui/text.h"

#include "../monsters/monster.h"

void drawFullScreenImg(GLuint* texture);

void drawPropertiesWindowList(TowerList* tl, int x, int y, TextStyle textCSS[], Text propTowerTexts[]);

void drawTowerSprite(Tower* tower, Sprite sprites[]);
void drawMonsterSprite(Monster* m, Sprite sprites[], int rotation);
void drawBuildingSprite(Building* build, Sprite sprites[]);
void rotateMonsterSprite(Monster *m, int angle, Sprite sprites[]);
void drawHealthBar(Monster* m, Sprite sprites[]);

void drawFireTower(Tower* t);

void globalDrawTowers(TowerList* tl, Sprite sprites[]);
void globalDrawBuildings(BuildingList* bl, Sprite sprites[]);
void globalDrawExplosions(ExplosionList* el, Sprite sprites[]);

#endif