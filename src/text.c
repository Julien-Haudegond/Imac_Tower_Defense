#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/text.h"


void loadText(const char* text, const char* fontName, SDL_Color color, int size, SDL_Surface** sFont, GLuint* texture) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    char fontPath[80] = "fonts/";
    strcat(fontPath, fontName);
    strcat(fontPath, ".ttf");

    TTF_Font* font = TTF_OpenFont(fontPath, size);

    if(!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        exit (EXIT_FAILURE);
    }


    *sFont = TTF_RenderText_Blended(font, text, color);

    if(!*sFont) {
        fprintf(stderr, "Error during loading the text area\n");
        exit (EXIT_FAILURE);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*sFont)->w, (*sFont)->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (*sFont)->pixels);
}

void renderText(SDL_Surface** sFont, GLuint* texture, int x , int y) {
    if(!*sFont) {
        fprintf(stderr, "Error during rendering the text area\n");
        exit (EXIT_FAILURE);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, *texture);

    x = x-((*sFont)->w)/2;
    y = y-((*sFont)->h)/2;
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x, y);
        glTexCoord2f(1,0); glVertex2f(x + (*sFont)->w, y);
        glTexCoord2f(1,1); glVertex2f(x + (*sFont)->w, y + (*sFont)->h);
        glTexCoord2f(0,1); glVertex2f(x, y + (*sFont)->h);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}