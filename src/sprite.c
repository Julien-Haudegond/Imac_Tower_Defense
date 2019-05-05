#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/sprite.h"
#include "../include/const.h"


int loadSpriteArea(SDL_Surface** image, const char* fichier) {
	char imagePath[70] = "images/sprites/";
	strcat(imagePath, fichier);

	*image = IMG_Load(imagePath);
    if(!*image) {
        fprintf(stderr, "Error during loading the image area\n");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int initSpriteTexture(SDL_Surface** image, GLuint* texture) {
	if(!*image) {
		fprintf(stderr, "Error with the image area during the initializing of the texture\n");
        exit (EXIT_FAILURE);
	}

	glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*image)->w, (*image)->h, 0, GL_RGB, GL_UNSIGNED_BYTE, (*image)->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    return EXIT_SUCCESS;
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