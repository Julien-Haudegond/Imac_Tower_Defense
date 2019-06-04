#ifndef GAME_H__
#define GAME_H__

#include <SDL/SDL.h>
#include <FMOD/fmod.h>

int playGame(SDL_Surface* surface, const char* itdPath);
void displayMoney();

#endif