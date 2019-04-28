#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/map_draw.h"
#include "../include/image.h"


void drawSquare(int filled) 
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

void constructibleArea() {
	glColor3ub(255, 200, 80);
	drawSquare(1);
}

void pathArea() {
	glColor3ub(255, 255, 255);
	drawSquare(1);
}

void nodeArea() {
	glColor3ub(0, 0, 0);
	drawSquare(1);
}

void startArea() {
	glColor3ub(0, 200, 0);
	drawSquare(1);
}

void endArea() {
	glColor3ub(200, 0, 0);
	drawSquare(1);
}

// A MODIFIER EN FONCTION DES INSTRUCTIONS ITD
GLuint createMapIDList(Image* imgPPM){
    GLuint id = glGenLists(1);
    Image I = *imgPPM;

    glNewList(id, GL_COMPILE);

    	for (int i = 0; i < I.h; i++) {
            for (int j = 0; j < I.w; j++) {
                glPushMatrix();
                    glTranslatef(0.5 + j, 0.5 + i, 0.);
                        if (I.pixel[j+i*I.w].r == 255 && I.pixel[j+i*I.w].g == 200 && I.pixel[j+i*I.w].b == 80) constructibleArea();
                        else if (I.pixel[j+i*I.w].r == 255 && I.pixel[j+i*I.w].g == 255 && I.pixel[j+i*I.w].b == 255) pathArea();
                        else if (I.pixel[j+i*I.w].r == 0 && I.pixel[j+i*I.w].g == 0 && I.pixel[j+i*I.w].b == 0) nodeArea();
                        else if (I.pixel[j+i*I.w].r == 0 && I.pixel[j+i*I.w].g == 200 && I.pixel[j+i*I.w].b == 0) startArea();
                        else if (I.pixel[j+i*I.w].r == 200 && I.pixel[j+i*I.w].g == 0 && I.pixel[j+i*I.w].b == 0) endArea();
                glPopMatrix();
            }
    	}
        	
    glEndList();

    return id;
}