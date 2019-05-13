#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/window.h"
#include "../include/const.h"

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, GL_VIEW_WIDTH, GL_VIEW_HEIGHT, 0); //Grid (let disabled because Window mode seems better)
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0); //Window
}

//Window coord will be in the center of the bloc
int gridCoordToWindowCoord(int grid_coord) {
    int offset = (int) GL_SPRITE_SIZE / 2;

    return (grid_coord * GL_SPRITE_SIZE + offset);
}

int windowCoordToGridCoord(int win_coord) {
    return (win_coord / GL_SPRITE_SIZE);
}

int windowCoordToBlocCenter(int win_coord) {
    int grid_coord = windowCoordToGridCoord(win_coord);

    return gridCoordToWindowCoord(grid_coord);
}