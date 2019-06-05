#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "const.h"

#include "gui/map_draw.h"
#include "gui/sprite.h"
#include "gui/window.h"
#include "gui/image.h"


void drawGridSquare(int filled) {
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}

void drawWindowSquare(int filled) {
    float offset = (float) GL_SPRITE_SIZE / 2;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( offset , - offset);
    glVertex2f( offset , offset);
    glVertex2f( - offset , offset);
    glVertex2f( - offset , - offset);
    glVertex2f( offset , - offset);

    glEnd();
}

void drawFullScreen(uint r, uint g, uint b, uint a) {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);

            glColor4ub(r, g, b, a);
            
            glVertex2f(0., 0.);
            glVertex2f( WINDOW_WIDTH , 0.);
            glVertex2f( WINDOW_WIDTH , WINDOW_HEIGHT);
            glVertex2f(0., WINDOW_HEIGHT);

        glEnd();

        glDisable(GL_BLEND);
    glPopAttrib();
    glPopMatrix();
}

void drawPropertiesScreen(uint r, uint g, uint b, uint a) {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);

            glColor4ub(r, g, b, a);
            
            glVertex2f( 0 , WINDOW_HEIGHT);
            glVertex2f( 200 , WINDOW_HEIGHT);
            glVertex2f( 200 , WINDOW_HEIGHT - 100);
            glVertex2f( 0 , WINDOW_HEIGHT - 100);

        glEnd();

        glDisable(GL_BLEND);
    glPopAttrib();
    glPopMatrix();
}


///// DEBUG DRAW FUNCTIONS

GLuint debugDrawIDList(Image* imgPPM){
    ///// VARIABLES
    GLuint id = glGenLists(1);
    Image I = *imgPPM;
    float offset = GL_SPRITE_SIZE / 2.;
    

    ///// CODE

    glNewList(id, GL_COMPILE);

        for (int i = 0; i < I.h; i++) {
            for (int j = 0; j < I.w; j++) {
                glPushMatrix();
                    glTranslatef(GL_SPRITE_SIZE*j + offset, GL_SPRITE_SIZE*i + offset, 0.);
                        if (I.pixel[j+i*I.w].r == 255 && I.pixel[j+i*I.w].g == 200 && I.pixel[j+i*I.w].b == 80) debug_constructibleArea();
                        else if (I.pixel[j+i*I.w].r == 255 && I.pixel[j+i*I.w].g == 255 && I.pixel[j+i*I.w].b == 255) debug_pathArea();
                        else if (I.pixel[j+i*I.w].r == 0 && I.pixel[j+i*I.w].g == 0 && I.pixel[j+i*I.w].b == 0) debug_nodeArea();
                        else if (I.pixel[j+i*I.w].r == 0 && I.pixel[j+i*I.w].g == 200 && I.pixel[j+i*I.w].b == 0) debug_startArea();
                        else if (I.pixel[j+i*I.w].r == 200 && I.pixel[j+i*I.w].g == 0 && I.pixel[j+i*I.w].b == 0) debug_endArea();
                glPopMatrix();
            }
        }
            
    glEndList();

    return id;
}

GLuint debugDrawNodesIDList(Node nodesArray[], int* nbOfNodes) {
    GLuint id = glGenLists(1);

    glNewList(id, GL_COMPILE);

    for(int i = 0; i < *nbOfNodes; i++) {
        glPushMatrix();
            glTranslatef(nodesArray[i].win_x, nodesArray[i].win_y, 0.);
            drawWindowSquare(1);
        glPopMatrix();
    }
            
    glEndList();

    return id;
}

void debug_constructibleArea() {
	glColor3ub(255, 200, 80);
	drawWindowSquare(1);
}

void debug_pathArea() {
	glColor3ub(255, 255, 255);
	drawWindowSquare(1);
}

void debug_nodeArea() {
	glColor3ub(0, 0, 0);
	drawWindowSquare(1);
}

void debug_startArea() {
	glColor3ub(0, 200, 0);
	drawWindowSquare(1);
}

void debug_endArea() {
	glColor3ub(200, 0, 0);
	drawWindowSquare(1);
}


///// DRAW MAP

GLuint createMapIDList(Image* imgPPM, ItdColorInstruction itdInstructions[], Sprite sprites[]) {
    ///// VARIABLES
    GLuint id = glGenLists(1);
    Image I = *imgPPM;
    float offset = GL_SPRITE_SIZE / 2;

    ItdColorInstruction construct, path, node, in, out;
  

    ///// CODE

    //Initialize the ITD colors (avoid future errors)
    construct.r = construct.g = construct.b = -1;
    path.r = path.g = path.b = -1;
    node.r = node.g = node.b = -1;
    in.r = in.g = in.b = -1;
    out.r = out.g = out.b = -1;

    //Get the color of each ITD instructions
    for(int j = 0; j < NUMBER_INSTRUCT; j++) {
        if(strcmp(itdInstructions[j].name, "construct") == 0) {
            construct.r = itdInstructions[j].r;
            construct.g = itdInstructions[j].g;
            construct.b = itdInstructions[j].b;
        }
        else if(strcmp(itdInstructions[j].name, "chemin") == 0) {
            path.r = itdInstructions[j].r;
            path.g = itdInstructions[j].g;
            path.b = itdInstructions[j].b;
        }
        else if(strcmp(itdInstructions[j].name, "noeud") == 0) {
            node.r = itdInstructions[j].r;
            node.g = itdInstructions[j].g;
            node.b = itdInstructions[j].b;
        }
        else if(strcmp(itdInstructions[j].name, "in") == 0) {
            in.r = itdInstructions[j].r;
            in.g = itdInstructions[j].g;
            in.b = itdInstructions[j].b;
        }
        else if(strcmp(itdInstructions[j].name, "out") == 0) {
            out.r = itdInstructions[j].r;
            out.g = itdInstructions[j].g;
            out.b = itdInstructions[j].b;
        }
    }

    //Draw the map
    glNewList(id, GL_COMPILE);

        for (int i = 0; i < I.h; i++) {
            for (int j = 0; j < I.w; j++) {
                glPushMatrix();
                    glTranslatef(GL_SPRITE_SIZE*j + offset, GL_SPRITE_SIZE*i + offset, 0.);
                        if (I.pixel[j+i*I.w].r == construct.r && I.pixel[j+i*I.w].g == construct.g && I.pixel[j+i*I.w].b == construct.b) drawSprite(&(sprites[0].texture)); //Construct
                        else if (I.pixel[j+i*I.w].r == path.r && I.pixel[j+i*I.w].g == path.g && I.pixel[j+i*I.w].b == path.b) drawSprite(&(sprites[1].texture)); //Path
                        else if (I.pixel[j+i*I.w].r == node.r && I.pixel[j+i*I.w].g == node.g && I.pixel[j+i*I.w].b == node.b) drawSprite(&(sprites[1].texture)); //Node
                        else if (I.pixel[j+i*I.w].r == in.r && I.pixel[j+i*I.w].g == in.g && I.pixel[j+i*I.w].b == in.b) drawSprite(&(sprites[1].texture)); //In
                        else if (I.pixel[j+i*I.w].r == out.r && I.pixel[j+i*I.w].g == out.g && I.pixel[j+i*I.w].b == out.b) drawSprite(&(sprites[1].texture)); //Out
                        else nonConstructibleArea();
                glPopMatrix();
            }
        }
            
    glEndList();

    return id;
}

void nonConstructibleArea() {
    glColor3ub(0, 200, 220);
    drawWindowSquare(1);
}



///// CHECK MAP EVOLUTION

void availableArea(int mouse_x, int mouse_y, Sprite sprites[]) {
    int center_x = windowCoordToBlocCenter(mouse_x);
    int center_y = windowCoordToBlocCenter(mouse_y);

    glPushMatrix();
        glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
        drawSprite(&(sprites[2].texture));
    glPopMatrix();
}

void nonAvailableArea(int mouse_x, int mouse_y, Sprite sprites[]) {
    int center_x = windowCoordToBlocCenter(mouse_x);
    int center_y = windowCoordToBlocCenter(mouse_y);

    glPushMatrix();
        glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
        drawSprite(&(sprites[3].texture));
    glPopMatrix();
}


//Return 1 if true and 0 if false
int isItAvailableArea(int x, int y, Image* ppm, ItdColorInstruction itdInstructions[], TowerList* tl, BuildingList* bl) {
    ///// VARIABLES
    int grid_x = windowCoordToGridCoord(x);
    int grid_y = windowCoordToGridCoord(y);

    ItdColorInstruction construct;

    Pixel current_pixel = ppm->pixel[(grid_y*ppm->w) + grid_x];


    ///// CODE

    //Initialize the ITD colors (avoid future errors)
    construct.r = construct.g = construct.b = -1;

    //Get constructible color components
    for(int i = 0; i < NUMBER_INSTRUCT; i++) {
        if(strcmp(itdInstructions[i].name, "construct") == 0) {
            construct.r = itdInstructions[i].r;
            construct.g = itdInstructions[i].g;
            construct.b = itdInstructions[i].b;
            break;
        }     
    }

    //If the bloc is on a constructible area (at the beginning)
    if(current_pixel.r == construct.r && current_pixel.g == construct.g && current_pixel.b == construct.b) {
        //CHECK THE TOWERS
        if(tl->tower) {
            TowerList* tmp = tl;
            
            if(tl->tower->x == grid_x && tl->tower->y == grid_y) return 0;

            while(tmp->nextTower) {
                tmp = tmp->nextTower;
                if(tmp->tower) {
                    if(tmp->tower->x == grid_x && tmp->tower->y == grid_y) return 0;
                }
            }
        }

        //CHECK THE BUILDINGS
        if(bl->build) {
            BuildingList* tmp2 = bl;
            
            if(bl->build->x == grid_x && bl->build->y == grid_y) return 0;

            while(tmp2->nextBuild) {
                tmp2 = tmp2->nextBuild;
                if(tmp2->build) {
                    if(tmp2->build->x == grid_x && tmp2->build->y == grid_y) return 0;
                }
            }
        }


        return 1;
    }
    else {
        return 0;
    }
}

int constructionGuides(int x, int y, Image* ppm, ItdColorInstruction itdInstructions[], Sprite sprites[], TowerList* tl, BuildingList* bl) {
    int value = isItAvailableArea(x, y, ppm, itdInstructions, tl, bl);

    if(value != 1 && value != 0) {
        fprintf(stderr, "Error: we can't know if the area is available or not\n");
        exit(EXIT_FAILURE);
    }

    if(value == 1) {
        availableArea(x, y, sprites);
        return 1;
    }
    else if(value == 0) {
        nonAvailableArea(x, y, sprites);
    }

    return 0;
}

void drawTowerGuides(int mouse_x, int mouse_y, TowerType type, Sprite sprites[]) {
    int center_x = windowCoordToBlocCenter(mouse_x);
    int center_y = windowCoordToBlocCenter(mouse_y);

    switch(type) {

        case LASER:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[4].texture));
            glPopMatrix();

            break;

        case ROCKET:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[5].texture));
            glPopMatrix();

            break;

        case ELECTRIC:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[6].texture));
            glPopMatrix();

            break;

        case WATER:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[7].texture));
            glPopMatrix();

            break;
    }
}


void drawBuildingGuides(int mouse_x, int mouse_y, BuildingType type, Sprite sprites[]) {
    int center_x = windowCoordToBlocCenter(mouse_x);
    int center_y = windowCoordToBlocCenter(mouse_y);

    switch(type) {

        case RADAR:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[11].texture));
            glPopMatrix();

            break;

        case FACTORY:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[12].texture));
            glPopMatrix();

            break;

        case AMMO:
            glPushMatrix();
                glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
                drawSprite(&(sprites[13].texture));
            glPopMatrix();

            break;
    }
}