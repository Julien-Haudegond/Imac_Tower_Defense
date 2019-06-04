#ifndef END_GAME_H__
#define END_GAME_H__

#include "../include/sprite.h"
#include "../include/text.h"

typedef struct EndScreen {
	int status;
	int frame;
} EndScreen;

EndScreen createEndScreen();

void drawEndScreen(EndScreen* screen, Sprite sprites[], Text texts[]);

#endif 