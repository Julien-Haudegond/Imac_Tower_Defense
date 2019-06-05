#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "const.h"

#include "animations/explosion.h"
#include "gui/sprite.h"
#include "gui/window.h"


/***** EXPLOSION *****/

Explosion* createExplosion(int x, int y) {
    Explosion* expl = malloc(sizeof(Explosion));
    
    if(!expl) {
        fprintf(stderr, "Error: bad memory allocation to make a new explosion.\n");
        exit(EXIT_FAILURE);
    }

    int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

    expl->x = grid_x;
    expl->y = grid_y;
    expl->win_x = gridCoordToWindowCoord(grid_x);
    expl->win_y = gridCoordToWindowCoord(grid_y);

    expl->frame = 0;

    return expl;
};

void printExplosion(Explosion* expl) {
    printf("Grid (%d,%d) / Window (%d,%d)\n", expl->x, expl->y, expl->win_x, expl->win_y);
    printf("Frame: %d \n", expl->frame);
}


/***** EXPLOSION LIST *****/


ExplosionList* createEmptyExplosionList() {
    ExplosionList* el = malloc(sizeof(ExplosionList));
    el->explosion = NULL;
    el->nextExplosion = NULL;

    return el;
}

void freeExplosionList(ExplosionList* el) {
    if(el) {
        if(el->explosion) {
            free(el->explosion);
        }
        if(el->nextExplosion) {
            freeExplosionList(el->nextExplosion);
        }
        free(el);
    }
}



void addExplosion(ExplosionList* el, int x, int y) {
    if(!el) {
        fprintf(stderr, "Error: no explosion list\n");
        exit(EXIT_FAILURE);
    }

    if(el->explosion == NULL) {
        el->explosion = createExplosion(x, y);
        return;
    }

    while(el->nextExplosion != NULL) {
        el = el->nextExplosion;
    }
    
    el->nextExplosion = malloc(sizeof(ExplosionList));
    el = el->nextExplosion;
    el->explosion = createExplosion(x, y);
    el->nextExplosion = NULL;
}


ExplosionList* deleteExplosion(ExplosionList* head) {
    if(!head) {
        fprintf(stderr, "Error : no explosion list (deleteExplosion)\n");
        exit(EXIT_FAILURE);
    }

    ExplosionList* tmp = head;
    ExplosionList* prev = head;

    //If the list is empty
    if(tmp->explosion == NULL && tmp->nextExplosion == NULL) {
        return tmp;
    }

    //If only one explosion in the list and we delete it
    if((tmp->explosion->frame >= 12) && tmp->nextExplosion == NULL) {
        free(tmp->explosion);
        tmp->explosion = NULL;
        tmp->nextExplosion = NULL;

        return tmp;
    }

    //If the first one is the good explosion to delete but there are several explosions in the list
    if(tmp->explosion != NULL && tmp->nextExplosion != NULL && tmp->explosion->frame >= 12) {
        head = tmp->nextExplosion;
        free(tmp->explosion);
        free(tmp);

        return head;
    }

    while(tmp) {
        if(tmp->explosion) {
            if(tmp->explosion->frame >= 12) {
                prev->nextExplosion = tmp->nextExplosion;
                free(tmp->explosion);
                free(tmp);

                break;
            }
            else {
                prev = tmp;
                tmp = tmp->nextExplosion;           
            }
        }
    }

    return head;
}


void printExplosionList(ExplosionList* el) {

    if(!el) {
        fprintf(stderr, "Error : no explosion list\n");
        exit(EXIT_FAILURE);
    }

    int counter = 1;
    if(el->explosion != NULL){
        // a optimiser
        while(el->nextExplosion != NULL){
            printf("Explosion %d \n", counter);
            printExplosion(el->explosion);
            el = el->nextExplosion;
            counter++;
        }
        if(el->nextExplosion == NULL){
        //printing last tower
            printf("Explosion %d \n", counter);
            printExplosion(el->explosion);
        }
    }
    if(el->explosion == NULL && el->nextExplosion == NULL) {
        printf("Explosion list is empty.\n");
    }
    printf("\n");
}





/***** ANIMATION *****/

void explodeSpriteSheet(GLuint* texture, Explosion* expl) {
	float offset = GL_SPRITE_SIZE / 2;

    int frame = expl->frame;

    int center_x = expl->win_x;
    int center_y = expl->win_y;

    //If the explosion is over, we leave the function
    if(frame >= 12) {
        return;
    }

    float x_min_texture = (expl->frame*(0.33));
    float y_min_texture = 0; //For frame = 0 ||  1 || 2

    if(expl->frame >= 3 && expl->frame <= 5) {
    	y_min_texture = 0.25;
    }
    else if(expl->frame >= 6 && expl->frame <= 8) {
    	y_min_texture = 0.5;
    }
    else if(expl->frame >= 9 && expl->frame <= 11) {
    	y_min_texture = 0.75;
    }

    float x_max_texture = x_min_texture + 0.33;
    float y_max_texture = y_min_texture + 0.25;


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glPushMatrix();

	    //glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
        glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
        glScalef(2.5, 2.5, 2.5);

	    glBegin(GL_QUADS);

	    
	        glTexCoord2f(x_min_texture, y_max_texture);
	        glVertex2f(- offset, offset);

	        glTexCoord2f(x_max_texture, y_max_texture);
	        glVertex2f(offset, offset);

	        glTexCoord2f(x_max_texture, y_min_texture);
	        glVertex2f(offset, - offset);

	        glTexCoord2f(x_min_texture, y_min_texture);
	        glVertex2f(- offset, - offset);


	    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    expl->frame++;
}