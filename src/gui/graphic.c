#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "const.h"

#include "gui/graphic.h"
#include "gui/text.h"
#include "gui/map_draw.h"
#include "gui/sprite.h"

void drawFullScreenImg(GLuint* texture) {
    glPushMatrix();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, *texture);

        glBegin(GL_QUADS);

        glTexCoord2f(0,0);
        glVertex2f(0., 0.);

        glTexCoord2f(1,0);
        glVertex2f( WINDOW_WIDTH , 0.);

        glTexCoord2f(1,1);
        glVertex2f( WINDOW_WIDTH , WINDOW_HEIGHT);

        glTexCoord2f(0,1);
        glVertex2f(0., WINDOW_HEIGHT);            

        glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}


void drawPropertiesWindowList(TowerList* tl, int x, int y, TextStyle textCSS[], Text propTowerTexts[]) {
    if(!tl) {
        fprintf(stderr, "Error : no tower list (createPropertiesWindowList)\n");
        exit(EXIT_FAILURE);
    }

    ///// VARIABLES
    Tower* t = malloc(sizeof(Tower));

    if(!t) {
        fprintf(stderr, "Error : bad memory allocation (createPropertiesWindowList)\n");
        exit(EXIT_FAILURE);        
    }

    getTowerInfosFromPosition(&t, tl, x, y); //Better than getTower directly because of the free memory at the end of the function

        //GET POSITION DATA
        char text1[20] = {0};
        strcat(text1, "Position: (");
            char int2string[20];
            snprintf(int2string, sizeof(int2string), "%d", t->x);
        strcat(text1, int2string);
        strcat(text1, ",");
            for(int i = 0; i < 20; i++) {
                int2string[i] = 0;
            }
            snprintf(int2string, sizeof(int2string), "%d", t->y);
        strcat(text1, int2string);
        strcat(text1, ")");
            for(int i = 0; i < 20; i++) {
                int2string[i] = 0;
            }                    

        //GET RANGE DATA
        char text2[20] = {0};
        strcat(text2, "Range: ");
            snprintf(int2string, sizeof(int2string), "%d", t->range);
        strcat(text2, int2string);
            for(int i = 0; i < 20; i++) {
                int2string[i] = 0;
            }
        
        //GET DAMAGE DATA                                   
        char text3[20] = {0};
        strcat(text3, "Damage: ");
            snprintf(int2string, sizeof(int2string), "%d", t->dmg);
        strcat(text3, int2string);
            for(int i = 0; i < 20; i++) {
                int2string[i] = 0;
            }

        //GET FIRESPEED DATA
        char text4[20] = {0};
        strcat(text4, "Firespeed: ");
            snprintf(int2string, sizeof(int2string), "%d", t->firespeed); //Actually a float and not a int but... you know
        strcat(text4, int2string);
            for(int i = 0; i < 20; i++) {
                int2string[i] = 0;
            }               

        //TEXTS
        loadText(text1, &(textCSS[2].font), textCSS[2].color, &(propTowerTexts[0].area), &(propTowerTexts[0].texture)); // Position
        loadText(text2, &(textCSS[2].font), textCSS[2].color, &(propTowerTexts[1].area), &(propTowerTexts[1].texture)); // Range
        loadText(text3, &(textCSS[2].font), textCSS[2].color, &(propTowerTexts[2].area), &(propTowerTexts[2].texture)); // Damage
        loadText(text4, &(textCSS[2].font), textCSS[2].color, &(propTowerTexts[3].area), &(propTowerTexts[3].texture)); // Firespeed

    ///// CODE

    glPushMatrix();

        drawPropertiesScreen(0, 0, 0, 200);

        renderLeftText(&propTowerTexts[0], 10 , 700);
        renderLeftText(&propTowerTexts[1], 10 , 720);
        renderLeftText(&propTowerTexts[2], 10 , 740);
        renderLeftText(&propTowerTexts[3], 10 , 760);

    glPopMatrix();

    free(t);
}


void drawTowerSprite(Tower* tower, Sprite sprites[]) {
    float x = (float) tower->win_x;
    float y = (float) tower->win_y;

    glPushMatrix();
        glTranslatef(x + 0.5, y + 0.5, 0.);

        switch(tower->type) {
            case LASER:
                drawSprite(&(sprites[4].texture));
                break;
            case ROCKET:
                drawSprite(&(sprites[5].texture));
                break;
            case ELECTRIC:
                drawSprite(&(sprites[6].texture));
                break;
            case WATER:
                drawSprite(&(sprites[7].texture));
                break;
            default:
                break;
        }
    glPopMatrix();
}


void drawMonsterSprite(Monster* m, Sprite sprites[], int angle) {
    float x = (float) m->win_x;
    float y = (float) m->win_y;

    glPushMatrix();
        glTranslatef(x + 0.5, y + 0.5, 0.);
        glRotatef(angle,0,0,1);
        switch(m->type) {
            case 0:
                drawSprite(&(sprites[8].texture));
                break;
            case 1:
                drawSprite(&(sprites[9].texture));
                break;
            default:
                break;
        }
    glPopMatrix();
}
    
void drawHealthBar(Monster* m, Sprite sprites[]){
    
    float x = (float) m->win_x;
    float y = (float) m->win_y;
    float health = m->health/m->healthMax;

    glPushMatrix();
        glTranslatef(x + 0.5, y - 15.5, 0.);
        glScalef(health,1.0,1.0);
        drawSprite(&(sprites[16].texture));
    glPopMatrix();
}

void rotateMonsterSprite(Monster *m, int angle, Sprite sprites[]){
    glPushMatrix();
         glRotatef(angle,0,0,1);
    glPopMatrix();
}

void drawBuildingSprite(Building* build, Sprite sprites[]) {
    float x = (float) build->win_x;
    float y = (float) build->win_y;

    glPushMatrix();
        glTranslatef(x + 0.5, y + 0.5, 0.);

        switch(build->type) {
            case RADAR:
                drawSprite(&(sprites[11].texture));
                break;
            case FACTORY:
                drawSprite(&(sprites[12].texture));
                break;
            case AMMO:
                drawSprite(&(sprites[13].texture));
                break;
            default:
                break;
        }
    glPopMatrix();    
}



void globalDrawTowers(TowerList* tl, Sprite sprites[]) {
    if(tl->tower) {
        TowerList* tmp = tl;
        drawTowerSprite(tmp->tower, sprites);

        while(tmp->nextTower) {
            tmp = tmp->nextTower;
            if(tmp->tower) {
                drawTowerSprite(tmp->tower, sprites);
            }
        }
    }
}

void globalDrawBuildings(BuildingList* bl, Sprite sprites[]) {
    if(bl->build) {
        BuildingList* tmp = bl;
        drawBuildingSprite(tmp->build, sprites);

        while(tmp->nextBuild) {
            tmp = tmp->nextBuild;
            if(tmp->build) {
                drawBuildingSprite(tmp->build, sprites);
            }
        }
    }
}

void globalDrawExplosions(ExplosionList* el, Sprite sprites[]) {
    if(el->explosion) {
        ExplosionList* tmp = el;
        explodeSpriteSheet(&(sprites[17].texture), tmp->explosion);

        while(tmp->nextExplosion) {
            tmp = tmp->nextExplosion;
            if(tmp->explosion) {
                explodeSpriteSheet(&(sprites[17].texture), tmp->explosion);
            }
        }
    }    
}
