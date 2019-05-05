#ifndef SPRITE_H__
#define SPRITE_H__

#define MAX_SPRITES 20 

int loadSpriteArea(SDL_Surface** image, const char* fichier);
int initSpriteTexture(SDL_Surface** image, GLuint* texture);


#endif