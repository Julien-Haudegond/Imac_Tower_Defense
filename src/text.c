#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/text.h"

//HERE TO CHANGE THE TEXT STYLES (PLEASE DO NOT MODIFY ORDER)
void initTextCSS(TextStyle textCSS[]) {

    //Style 0
    textCSS[0].font = loadFont(FONT_1, 24);
    textCSS[0].color = (SDL_Color) {255, 0, 0, 0};

    //Style 1
    textCSS[1].font = loadFont(FONT_1, 24);
    textCSS[1].color = (SDL_Color) {255, 255, 255, 0};

    //Style 2
    textCSS[2].font = loadFont(FONT_1, 16);
    textCSS[2].color = (SDL_Color) {255, 255, 255, 0};

    //Style 3
    textCSS[3].font = loadFont(FONT_1, 46);
    textCSS[3].color = (SDL_Color) {255, 255, 0, 0};

    //Style 4
    textCSS[4].font = loadFont(FONT_1, 46);
    textCSS[4].color = (SDL_Color) {255, 0, 0, 0};
}


//HERE TO CHANGE THE STATIC TEXTS (PLEASE DO NOT MODIFY ORDER)
void fillTextsArrays(TextStyle textCSS[], Text texts[]) {

    //Text 0 : Press 'h' to get help !
    loadText("Press 'h' to get some help !", &(textCSS[0].font), textCSS[0].color, &(texts[0].area), &(texts[0].texture));

    //Text 1 : Money (need to be reload each time, so in another function)

    //Text 2 : GUARDIAN OF THE GALAXY !
    loadText("Guardian of the Galaxy", &(textCSS[3].font), textCSS[3].color, &(texts[2].area), &(texts[2].texture));

    //Text 3 : You failed !
    loadText("You failed !", &(textCSS[4].font), textCSS[4].color, &(texts[3].area), &(texts[3].texture));
}


/************************************************************************/


void initTextCSSToNull(TextStyle textCSS[]) {
    for(int i = 0; i < MAX_CSS; i++) {
        textCSS[i].font = NULL;
    }
}

void freeTextCSS(TextStyle textCSS[]) {
    for(int i = 0; i < MAX_CSS; i++) {
        TTF_CloseFont(textCSS[i].font);
    }
}

void initTextsToNull(Text texts[]) {
    for(int i = 0; i < MAX_TEXTS; i++) {
        texts[i].area = NULL;
    }
}

void freeTexts(Text texts[]) {
    for(int i = 0; i < MAX_TEXTS; i++) {
        SDL_FreeSurface(texts[i].area);
        glDeleteTextures(1, &(texts[i].texture));
    }
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

void renderCenterText(Text* text, int x , int y) {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, text->texture);

    x = x-((text->area)->w)/2;
    y = y-((text->area)->h)/2;
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x, y);
        glTexCoord2f(1,0); glVertex2f(x + (text->area)->w, y);
        glTexCoord2f(1,1); glVertex2f(x + (text->area)->w, y + (text->area)->h);
        glTexCoord2f(0,1); glVertex2f(x, y + (text->area)->h);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void renderLeftText(Text* text, int x , int y) {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, text->texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x, y);
        glTexCoord2f(1,0); glVertex2f(x + (text->area)->w, y);
        glTexCoord2f(1,1); glVertex2f(x + (text->area)->w, y + (text->area)->h);
        glTexCoord2f(0,1); glVertex2f(x, y + (text->area)->h);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void renderRightText(Text* text, int x , int y) {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, text->texture);

    x = x-((text->area)->w);
    y = y-((text->area)->h)/2;
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(x, y);
        glTexCoord2f(1,0); glVertex2f(x + (text->area)->w, y);
        glTexCoord2f(1,1); glVertex2f(x + (text->area)->w, y + (text->area)->h);
        glTexCoord2f(0,1); glVertex2f(x, y + (text->area)->h);
    glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}



void loadIntegerText(int integer, TextStyle* textCSS, Text* text) {
    glGenTextures(1, &(text->texture));
    glBindTexture(GL_TEXTURE_2D, text->texture);

    char txt[10];
    snprintf(txt, sizeof(txt), "%d", integer);

    text->area = TTF_RenderText_Blended(textCSS->font, txt, textCSS->color);

    if(!(text->area)) {
        fprintf(stderr, "Error during loading the text area\n");
        exit (EXIT_FAILURE);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (text->area)->w, (text->area)->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (text->area)->pixels);
}