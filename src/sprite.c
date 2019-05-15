#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/sprite.h"
#include "../include/const.h"

/***** SPRITES ARRAY *****/

//HERE TO CHANGE THE SPRITES (PLEASE DO NOT MODIFY ORDER)
void fillSprites(SDL_Surface* sprite_img[], GLuint sprite_texture[]) {

    //Texture 0 : Constructible area
    loadSpriteArea(&sprite_img[0], "construct_area_RGBA.png");
    initSpriteTexture(&sprite_img[0], &sprite_texture[0]);

    //Texture 1 : Path area
    loadSpriteArea(&sprite_img[1], "path_area_RGBA.png");
    initSpriteTexture(&sprite_img[1], &sprite_texture[1]);

    //Texture 2 : Available area
    loadSpriteArea(&sprite_img[2], "available_area_RGBA.png");
    initSpriteTexture(&sprite_img[2], &sprite_texture[2]);

    //Texture 3 : Non available area
    loadSpriteArea(&sprite_img[3], "nonAvailable_area_RGBA.png");
    initSpriteTexture(&sprite_img[3], &sprite_texture[3]);

    //Texture 4 : TOWER Laser
    loadSpriteArea(&sprite_img[4], "Tower_Laser_RGBA.png");
    initSpriteTexture(&sprite_img[4], &sprite_texture[4]);

    //Texture 5 : TOWER Rocket
    loadSpriteArea(&sprite_img[5], "Tower_Rocket_RGBA.png");
    initSpriteTexture(&sprite_img[5], &sprite_texture[5]);

    //Texture 6 : TOWER Electric
    loadSpriteArea(&sprite_img[6], "Tower_Electric_RGBA.png");
    initSpriteTexture(&sprite_img[6], &sprite_texture[6]);

    //Texture 7 : TOWER Water
    loadSpriteArea(&sprite_img[7], "Tower_Water_RGBA.png");
    initSpriteTexture(&sprite_img[7], &sprite_texture[7]);

}




/***** ONE SPRITE *****/

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*image)->w, (*image)->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (*image)->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    return EXIT_SUCCESS;
}

void drawSprite(GLuint* texture) {
	float offset = GL_SPRITE_SIZE / 2;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex2f(- offset, offset);

        glTexCoord2f(1,1);
        glVertex2f(offset, offset);

        glTexCoord2f(1,0);
        glVertex2f(offset, - offset);

        glTexCoord2f(0,0);
        glVertex2f(- offset, - offset);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}