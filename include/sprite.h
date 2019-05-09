#ifndef SPRITE_H__
#define SPRITE_H__

#define MAX_SPRITES 20 

//Sprites array
void fillSprites(SDL_Surface* sprite_img[], GLuint sprite_texture[]);

//One sprite
int loadSpriteArea(SDL_Surface** image, const char* fichier);
int initSpriteTexture(SDL_Surface** image, GLuint* texture);
void drawSprite(GLuint* texture);

#endif