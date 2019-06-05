#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "const.h"

#include "animations/end_game.h"

#include "gui/map_draw.h"
#include "gui/graphic.h"

EndScreen createEndScreen() {
	EndScreen screen;

	screen.status = -1; // -1 = undefined / 0 = loser / 1 = winner
	screen.frame = 0;

	return screen;
}

void drawEndScreen(EndScreen* screen, Sprite sprites[], Text texts[]) {
	int alphaBG = 0;
	int alphaFG = 250;

	int y_img = WINDOW_HEIGHT/4 - 100;

	alphaBG = (screen->frame)*10; //Need around 1 sec to get into deep black BG
	if(alphaBG >= 250) {
		alphaBG = 250;
	}

	if(screen->frame >= 25) { //Starting at 1 sec
		alphaFG = 250 - (screen->frame-25)*10;
		if(alphaFG <= 0) {
			alphaFG = 0;
		}
	}

	//Move the image vertically during 4 seconds
	if(screen->frame <= 100) {
		y_img = WINDOW_HEIGHT/4 - screen->frame;
	}

	//If undefined
	if(screen->status == -1) {
		return;
	}
	//If winner
	else if(screen->status == 1) {
		//Black BG
		drawFullScreen(0, 0, 0, alphaBG);

		//Starting at 1 sec
    	if(screen->frame >= 25) {
    		//TEXT
    		renderCenterText(&texts[2], 610, 500);

    		//Medal
			glPushMatrix();
				glTranslatef(WINDOW_WIDTH/4, y_img, 0);
				glScalef(0.5, 0.5, 0.5);
	    		drawFullScreenImg(&(sprites[18].texture));
	    	glPopMatrix();

	    	//Alpha cache screen
    		drawFullScreen(0, 0, 0, alphaFG);
    	}
	}
	//If loser
	else if(screen->status == 0) {
		//Black BG
		drawFullScreen(0, 0, 0, alphaBG);

		//Starting at 1 sec
    	if(screen->frame >= 25) {
    		//TEXT
    		renderCenterText(&texts[3], 610, 500);

    		//Skull
			glPushMatrix();
				glTranslatef(WINDOW_WIDTH/4, y_img, 0);
				glScalef(0.5, 0.5, 0.5);
	    		drawFullScreenImg(&(sprites[19].texture));
	    	glPopMatrix();

	    	//Alpha cache screen
    		drawFullScreen(0, 0, 0, alphaFG);
    	}
	}
	else {
		printf("There is a problem with the end screen status...");
	}

	screen->frame++;

}