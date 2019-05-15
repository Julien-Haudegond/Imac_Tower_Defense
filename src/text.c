#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/text.h"

//HERE TO CHANGE THE FONTS (PLEASE DO NOT MODIFY ORDER)
void initFontsArray(TTF_Font* fonts[]) {

    //Font 0
    fonts[0] = loadFont(FONT_1, 24);

}

//HERE TO CHANGE THE COLORS (PLEASE DO NOT MODIFY ORDER)
void initColorsArray(SDL_Color colors[]) {

    //Color 0 : Red color
    colors[0] = (SDL_Color) {255, 0, 0, 0};

}

//HERE TO CHANGE THE STATIC TEXTS (PLEASE DO NOT MODIFY ORDER)
void fillTextsArrays(TTF_Font* fonts[], SDL_Color colors[], SDL_Surface* text_area[], GLuint text_texture[]) {

    //Text 0 : Press 'h' to get help !
    loadText("Press 'h' to get some help !", &fonts[0], colors[0], &text_area[0], &text_texture[0]);
    
}






//Don't forget to close the font at the end
TTF_Font* loadFont(const char* fontName, int size) {
    char fontPath[80] = "fonts/";
    strcat(fontPath, fontName);
    strcat(fontPath, ".ttf");

    TTF_Font* font = TTF_OpenFont(fontPath, size);

    if(!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        exit (EXIT_FAILURE);
    }

    return font;
}

void loadText(const char* text, TTF_Font** font, SDL_Color color, SDL_Surface** sFont, GLuint* texture) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    if(!*font) {
        fprintf(stderr, "Error: no font available to load static text");
        exit (EXIT_FAILURE);
    }

    *sFont = TTF_RenderText_Blended(*font, text, color);

    if(!*sFont) {
        fprintf(stderr, "Error during loading the text area\n");
        exit (EXIT_FAILURE);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*sFont)->w, (*sFont)->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (*sFont)->pixels);
}

void renderCenterText(SDL_Surface** sFont, GLuint* texture, int x , int y) {
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

void renderLeftText(SDL_Surface** sFont, GLuint* texture, int x , int y) {
    if(!*sFont) {
        fprintf(stderr, "Error during rendering the text area\n");
        exit (EXIT_FAILURE);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x, y);
        glTexCoord2f(1,0); glVertex2f(x + (*sFont)->w, y);
        glTexCoord2f(1,1); glVertex2f(x + (*sFont)->w, y + (*sFont)->h);
        glTexCoord2f(0,1); glVertex2f(x, y + (*sFont)->h);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}