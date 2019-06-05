#ifndef END_GAME_H__
#define END_GAME_H__

#include "../structures/str_end_game.h"

#include "../gui/sprite.h"
#include "../gui/text.h"

EndScreen createEndScreen();

void drawEndScreen(EndScreen* screen, Sprite sprites[], Text texts[]);

#endif 