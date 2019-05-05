#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/map_draw.h"
#include "../include/const.h"

//INUTILE SI LA FONCTION RESIZE EST EN MODE WINDOW (ET NON GRID)
void drawGridSquare(int filled) 
{
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

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( GL_SPRITE_SIZE / 2. , - GL_SPRITE_SIZE / 2.);
    glVertex2f( GL_SPRITE_SIZE / 2. , GL_SPRITE_SIZE / 2.);
    glVertex2f( - GL_SPRITE_SIZE / 2. , GL_SPRITE_SIZE / 2.);
    glVertex2f( - GL_SPRITE_SIZE / 2. , - GL_SPRITE_SIZE / 2.);
    glVertex2f( GL_SPRITE_SIZE / 2. , - GL_SPRITE_SIZE / 2.);

    glEnd();
}

void drawSprite(GLuint* texture) {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glBegin(GL_QUADS);

        glTexCoord2f(0,0);
        glVertex2f(- GL_SPRITE_SIZE / 2., GL_SPRITE_SIZE / 2.);

        glTexCoord2f(1,0);
        glVertex2f(GL_SPRITE_SIZE / 2., GL_SPRITE_SIZE / 2.);

        glTexCoord2f(1,1);
        glVertex2f(GL_SPRITE_SIZE / 2., - GL_SPRITE_SIZE / 2.);

        glTexCoord2f(0,1);
        glVertex2f(- GL_SPRITE_SIZE / 2., - GL_SPRITE_SIZE / 2.);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
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

GLuint createMapIDList(Image* imgPPM, ItdColorInstruction itdInstructions[], GLuint sprite_text[]) {
    ///// VARIABLES
    GLuint id = glGenLists(1);
    Image I = *imgPPM;
    float offset = GL_SPRITE_SIZE / 2.;

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
                        if (I.pixel[j+i*I.w].r == construct.r && I.pixel[j+i*I.w].g == construct.g && I.pixel[j+i*I.w].b == construct.b) drawSprite(&sprite_text[0]); //Construct
                        else if (I.pixel[j+i*I.w].r == path.r && I.pixel[j+i*I.w].g == path.g && I.pixel[j+i*I.w].b == path.b) pathArea(); //Path
                        else if (I.pixel[j+i*I.w].r == node.r && I.pixel[j+i*I.w].g == node.g && I.pixel[j+i*I.w].b == node.b) pathArea(); //Node
                        else if (I.pixel[j+i*I.w].r == in.r && I.pixel[j+i*I.w].g == in.g && I.pixel[j+i*I.w].b == in.b) pathArea(); //In
                        else if (I.pixel[j+i*I.w].r == out.r && I.pixel[j+i*I.w].g == out.g && I.pixel[j+i*I.w].b == out.b) pathArea(); //Out
                        else nonConstructibleArea();
                glPopMatrix();
            }
        }
            
    glEndList();

    return id;
}


void constructibleArea() {
    glColor3ub(255, 200, 80);
    drawWindowSquare(1);
}

void pathArea() {
    glColor3ub(255, 255, 255);
    drawWindowSquare(1);
}

void nonConstructibleArea() {
    glColor3ub(0, 200, 220);
    drawWindowSquare(1);
}