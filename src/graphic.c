#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/const.h"
#include "../include/graphic.h"
#include "../include/text.h"
#include "../include/map_draw.h"
#include "../include/sprite.h"

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

GLuint createHelpList(GLuint help_window_texture[], Sprite sprites[]) {
    ///// VARIABLES
    GLuint id = glGenLists(1);

    SDL_Surface* text_area[MAX_TEXTS];

    for(int i =  0; i < MAX_TEXTS; i++) {
        text_area[i] = NULL;
    }

	    //Colors
	    SDL_Color color = {255, 255, 255, 0};

	    //Fonts
	    TTF_Font* font_24 = loadFont(FONT_1, 24);

	    	//Text 0 : SPACESHIPS
	    	loadText("SPACESHIPS", &font_24, color, &text_area[0], &help_window_texture[0]);

	    	//Text 1 : Press 'a' to make a 'laser spaceship' !
	    	loadText("Press 'a' to make a 'laser spaceship' | 500 ", &font_24, color, &text_area[1], &help_window_texture[1]);

	    	//Text 2 : Press 'z' to make a 'rocket spaceship' !
	    	loadText("Press 'z' to make a 'rocket spaceship' | 500 ", &font_24, color, &text_area[2], &help_window_texture[2]);

	    	//Text 3 : Press 'e' to make a 'electric spaceship' !
	    	loadText("Press 'e' to make a 'electric spaceship' | 500 ", &font_24, color, &text_area[3], &help_window_texture[3]);

	    	//Text 4 : Press 'r' to make a 'water spaceship' !
	    	loadText("Press 'r' to make a 'water spaceship' | 500 ", &font_24, color, &text_area[4], &help_window_texture[4]);

			//Text 5 : PLANETS
	    	loadText("PLANETS", &font_24, color, &text_area[5], &help_window_texture[5]);

	    	//Text 6 : Press 'q' to make a 'radar planet' !
	    	loadText("Press 'q' to make a 'radar planet' | 500 ", &font_24, color, &text_area[6], &help_window_texture[6]);

	    	//Text 7 : Press 's' to make a 'factory planet' !
	    	loadText("Press 's' to make a 'factory planet' | 500 ", &font_24, color, &text_area[7], &help_window_texture[7]);

	    	//Text 8 : Press 'd' to make a 'ammo planet' !
	    	loadText("Press 'd' to make a 'ammo planet' | 500 ", &font_24, color, &text_area[8], &help_window_texture[8]);

            //Text 9 : Press 'del' to delete a construction (give you back half of its price) !
            loadText("Press 'del' to delete a construction (give you back half of its price) !", &font_24, color, &text_area[9], &help_window_texture[9]);

            //Text 10 : Press 'esc' to leave the game !
            loadText("Press 'esc' to leave the game !", &font_24, color, &text_area[10], &help_window_texture[10]);


    ///// CODE
    
    glNewList(id, GL_COMPILE);

    	drawFullScreen(0, 0, 0, 200);

    	renderLeftText(&text_area[0], &help_window_texture[0], 100 , 50);
    	renderLeftText(&text_area[1], &help_window_texture[1], 100 , 100);
            glPushMatrix();
                glTranslatef(720, 112, 0);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[2], &help_window_texture[2], 100 , 150);
            glPushMatrix();
                glTranslatef(737, 162, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[3], &help_window_texture[3], 100 , 200);
            glPushMatrix();
                glTranslatef(762, 212, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[4], &help_window_texture[4], 100 , 250);
            glPushMatrix();
                glTranslatef(720, 262, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[5], &help_window_texture[5], 100 , 400);
    	renderLeftText(&text_area[6], &help_window_texture[6], 100 , 450);
            glPushMatrix();
                glTranslatef(680, 462, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[7], &help_window_texture[7], 100 , 500);
            glPushMatrix();
                glTranslatef(705, 512, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
    	renderLeftText(&text_area[8], &help_window_texture[8], 100 , 550);
            glPushMatrix();
                glTranslatef(665, 562, 0.);
                glScalef(0.7, 0.7, 1.);
                drawSprite(&(sprites[14].texture));
            glPopMatrix();
        renderLeftText(&text_area[9], &help_window_texture[9], 100 , 650);
        renderLeftText(&text_area[10], &help_window_texture[10], 100 , 725);        

    glEndList();

    /* Close the font */
    TTF_CloseFont(font_24);

    /* Free text surfaces */
    for(int i = 0; i < MAX_TEXTS; i++) {
        SDL_FreeSurface(text_area[i]);
    }

    return id;
}

GLuint createPropertiesWindowList(TowerList* tl, int x, int y, GLuint properties_window_texture[]) {
    if(!tl) {
        fprintf(stderr, "Error : no tower list (createPropertiesWindowList)\n");
        exit(EXIT_FAILURE);
    }

    ///// VARIABLES
    GLuint id = glGenLists(1);

    Tower* t = malloc(sizeof(Tower));

    if(!t) {
        fprintf(stderr, "Error : bad memory allocation (createPropertiesWindowList)\n");
        exit(EXIT_FAILURE);        
    }

    getTowerInfosFromPosition(&t, tl, x, y); //Better than getTower directly because of the free memory at the end of the function

    SDL_Surface* text_area[MAX_TEXTS];

    for(int i =  0; i < MAX_TEXTS; i++) {
        text_area[i] = NULL;
    }

        //Colors
        SDL_Color color = {255, 255, 255, 0};

        //Fonts
        TTF_Font* font = loadFont(FONT_1, 16);

                //GET POSITION DATA
                char text1[20] = {0};
                strcat(text1, "Position: (");
                    char int2string[20];
                    snprintf(int2string, sizeof(int2string), "%d", t->x);
                strcat(text1, int2string);
                strcat(text1, ",");
                    for(int i = 0; i < 10; i++) {
                        int2string[i] = 0;
                    }
                    snprintf(int2string, sizeof(int2string), "%d", t->y);
                strcat(text1, int2string);
                strcat(text1, ")");
                    for(int i = 0; i < 10; i++) {
                        int2string[i] = 0;
                    }                    

                //GET RANGE DATA
                char text2[20] = {0};
                strcat(text2, "Range: ");
                    snprintf(int2string, sizeof(int2string), "%d", t->range);
                strcat(text2, int2string);
                    for(int i = 0; i < 10; i++) {
                        int2string[i] = 0;
                    }
                
                //GET DAMAGE DATA                                   
                char text3[20] = {0};
                strcat(text3, "Damage: ");
                    snprintf(int2string, sizeof(int2string), "%d", t->dmg);
                strcat(text3, int2string);
                    for(int i = 0; i < 10; i++) {
                        int2string[i] = 0;
                    }

                //GET FIRESPEED DATA
                char text4[20] = {0};
                strcat(text4, "Firespeed: ");
                    snprintf(int2string, sizeof(int2string), "%.2f", t->firespeed); //Actually a float and not a int but... you know
                strcat(text4, int2string);
                    for(int i = 0; i < 10; i++) {
                        int2string[i] = 0;
                    }               


        //TEXTS
        loadText(text1, &font, color, &text_area[0], &properties_window_texture[0]); // Position
        loadText(text2, &font, color, &text_area[1], &properties_window_texture[1]); // Range
        loadText(text3, &font, color, &text_area[2], &properties_window_texture[2]); // Damage
        loadText(text4, &font, color, &text_area[3], &properties_window_texture[3]); // Firespeed

    ///// CODE

    glNewList(id, GL_COMPILE);

        drawPropertiesScreen(0, 0, 0, 200);

        renderLeftText(&text_area[0], &properties_window_texture[0], 10 , 700);
        renderLeftText(&text_area[1], &properties_window_texture[1], 10 , 720);
        renderLeftText(&text_area[2], &properties_window_texture[2], 10 , 740);
        renderLeftText(&text_area[3], &properties_window_texture[3], 10 , 760);

    glEndList();

    /* Close the font */
    TTF_CloseFont(font);

    /* Free text surfaces */
    for(int i = 0; i < MAX_TEXTS; i++) {
        SDL_FreeSurface(text_area[i]);
    }

    free(t);

    return id;
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