#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/graphic.h"
#include "../include/text.h"
#include "../include/map_draw.h"

GLuint createHelpList(GLuint text_texture[]) {
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
	    	loadText("SPACESHIPS", &font_24, color, &text_area[0], &text_texture[0]);

	    	//Text 1 : Press 'a' to make a 'laser spaceship' !
	    	loadText("Press 'a' to make a 'laser spaceship' | 250 $", &font_24, color, &text_area[1], &text_texture[1]);

	    	//Text 2 : Press 'z' to make a 'rocket spaceship' !
	    	loadText("Press 'z' to make a 'rocket spaceship' | 250 $", &font_24, color, &text_area[2], &text_texture[2]);

	    	//Text 3 : Press 'e' to make a 'electric spaceship' !
	    	loadText("Press 'e' to make a 'electric spaceship' | 250 $", &font_24, color, &text_area[3], &text_texture[3]);

	    	//Text 4 : Press 'r' to make a 'water spaceship' !
	    	loadText("Press 'r' to make a 'water spaceship' | 250 $", &font_24, color, &text_area[4], &text_texture[4]);

			//Text 5 : PLANETS
	    	loadText("PLANETS", &font_24, color, &text_area[5], &text_texture[5]);

	    	//Text 6 : Press 'q' to make a 'radar planet' !
	    	loadText("Press 'q' to make a 'radar planet' | 250 $", &font_24, color, &text_area[6], &text_texture[6]);

	    	//Text 7 : Press 's' to make a 'factory planet' !
	    	loadText("Press 's' to make a 'factory planet' | 250 $", &font_24, color, &text_area[7], &text_texture[7]);

	    	//Text 8 : Press 'd' to make a 'ammo planet' !
	    	loadText("Press 'd' to make a 'ammo planet' | 250 $", &font_24, color, &text_area[8], &text_texture[8]);


    ///// CODE
    
    glNewList(id, GL_COMPILE);

    	drawFullScreen(0, 0, 0, 150);

    	renderLeftText(&text_area[0], &text_texture[0], 100 , 50);
    	renderLeftText(&text_area[1], &text_texture[1], 100 , 100);
    	renderLeftText(&text_area[2], &text_texture[2], 100 , 150);
    	renderLeftText(&text_area[3], &text_texture[3], 100 , 200);
    	renderLeftText(&text_area[4], &text_texture[4], 100 , 250);
    	renderLeftText(&text_area[5], &text_texture[5], 100 , 400);
    	renderLeftText(&text_area[6], &text_texture[6], 100 , 450);
    	renderLeftText(&text_area[7], &text_texture[7], 100 , 500);
    	renderLeftText(&text_area[8], &text_texture[8], 100 , 550);

    glEndList();

    /* Close the font */
    TTF_CloseFont(font_24);

    /* Free text surfaces */
    for(int i = 0; i < MAX_TEXTS; i++) {
        SDL_FreeSurface(text_area[i]);
    }

    return id;
}