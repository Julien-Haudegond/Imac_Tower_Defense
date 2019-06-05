#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "const.h"

#include "gui/sprite.h"
#include "gui/window.h"

/***** SPRITES ARRAY *****/

void initSpritesToNull(Sprite sprites[]) {
    for(int i =  0; i < MAX_SPRITES; i++) {
        sprites[i].area = NULL;
    }
}

void freeSprites(Sprite sprites[]) {
    for(int i = 0; i < MAX_SPRITES; i++) {
        SDL_FreeSurface(sprites[i].area);
        glDeleteTextures(1, &(sprites[i].texture));   
    }
}

//HERE TO CHANGE THE SPRITES (PLEASE DO NOT MODIFY ORDER)
void fillSprites(Sprite sprites[]) {

    //Texture 0 : Constructible area
    loadSpriteArea(&(sprites[0].area), "construct_area_RGBA.png");
    initSpriteTexture(&(sprites[0].area), &(sprites[0].texture));

    //Texture 1 : Path area
    loadSpriteArea(&(sprites[1].area), "path_area_RGBA.png");
    initSpriteTexture(&(sprites[1].area), &(sprites[1].texture));

    //Texture 2 : Available area
    loadSpriteArea(&(sprites[2].area), "available_area_RGBA.png");
    initSpriteTexture(&(sprites[2].area), &(sprites[2].texture));

    //Texture 3 : Non available area
    loadSpriteArea(&(sprites[3].area), "nonAvailable_area_RGBA.png");
    initSpriteTexture(&(sprites[3].area), &(sprites[3].texture));

    //Texture 4 : TOWER Laser
    loadSpriteArea(&(sprites[4].area), "Tower_Laser_RGBA.png");
    initSpriteTexture(&(sprites[4].area), &(sprites[4].texture));

    //Texture 5 : TOWER Rocket
    loadSpriteArea(&(sprites[5].area), "Tower_Rocket_RGBA.png");
    initSpriteTexture(&(sprites[5].area), &(sprites[5].texture));

    //Texture 6 : TOWER Electric
    loadSpriteArea(&(sprites[6].area), "Tower_Electric_RGBA.png");
    initSpriteTexture(&(sprites[6].area), &(sprites[6].texture));

    //Texture 7 : TOWER Water
    loadSpriteArea(&(sprites[7].area), "Tower_Water_RGBA.png");
    initSpriteTexture(&(sprites[7].area), &(sprites[7].texture));

    //Texture 8 : MONSTER Giant
    loadSpriteArea(&(sprites[8].area), "Monster_Giant_RGBA.png");
    initSpriteTexture(&(sprites[8].area), &(sprites[8].texture));

    //Texture 9 : MONSTER Swarmling
    loadSpriteArea(&(sprites[9].area), "Monster_swarmling_RGBA.png");
    initSpriteTexture(&(sprites[9].area), &(sprites[9].texture));

    //Texture 10 : Delete Sprite
    loadSpriteArea(&(sprites[10].area), "delete_area_RGBA.png");
    initSpriteTexture(&(sprites[10].area), &(sprites[10].texture));

    //Texture 11 : BUILDING Radar
    loadSpriteArea(&(sprites[11].area), "Building_Radar_RGBA.png");
    initSpriteTexture(&(sprites[11].area), &(sprites[11].texture));

    //Texture 12 : BUILDING Factory
    loadSpriteArea(&(sprites[12].area), "Building_Factory_RGBA.png");
    initSpriteTexture(&(sprites[12].area), &(sprites[12].texture));

    //Texture 13 : BUILDING Ammo
    loadSpriteArea(&(sprites[13].area), "Building_Ammo_RGBA.png");
    initSpriteTexture(&(sprites[13].area), &(sprites[13].texture));

    //Texture 14 : MONEY
    loadSpriteArea(&(sprites[14].area), "money_RGBA.png");
    initSpriteTexture(&(sprites[14].area), &(sprites[14].texture));

    //Texture 15 : HELP
    loadSpriteArea(&(sprites[15].area), "whole_screens/Help_Img.png");
    initSpriteTexture(&(sprites[15].area), &(sprites[15].texture));

    //Texture 16 : HEALTH
    loadSpriteArea(&(sprites[16].area), "health.png");
    initSpriteTexture(&(sprites[16].area), &(sprites[16].texture));

    //Texture 17 : EXPLOSION Sheet
    loadSpriteArea(&(sprites[17].area), "Explosion_SpriteSheet.png");
    initSpriteTexture(&(sprites[17].area), &(sprites[17].texture));

    //Texture 18 : Medal
    loadSpriteArea(&(sprites[18].area), "whole_screens/Medal.png");
    initSpriteTexture(&(sprites[18].area), &(sprites[18].texture));

    //Texture 19 : Skull
    loadSpriteArea(&(sprites[19].area), "whole_screens/Skull.png");
    initSpriteTexture(&(sprites[19].area), &(sprites[19].texture));

    //Texture 20 : Skull
    loadSpriteArea(&(sprites[20].area), "whole_screens/pause.png");
    initSpriteTexture(&(sprites[20].area), &(sprites[20].texture));
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

void drawSpriteHere(GLuint* texture, int x, int y) {
    int center_x = windowCoordToBlocCenter(x);
    int center_y = windowCoordToBlocCenter(y);

    glPushMatrix();
        glTranslatef(center_x + 0.5, center_y + 0.5 , 0.);
        drawSprite(texture);
    glPopMatrix();
}