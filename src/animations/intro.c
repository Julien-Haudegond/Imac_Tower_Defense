#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FMOD/fmod.h>

#include "const.h"

#include "animations/intro.h"

#include "app/menu.h"

#include "gui/window.h"
#include "gui/sprite.h"
#include "gui/graphic.h"


int playIntro() {

    /* Initializing SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(stderr, "Error: during SDL_Init.\n");
        return EXIT_FAILURE;
    }

    /* Open a window and create the OpenGL context */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Title of the window */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    /* Initializing FMOD */
    FMOD_SYSTEM* system;
    FMOD_SOUND* music;
    FMOD_RESULT result;
    FMOD_CHANNEL* channel;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

        //Opening the music
        result = FMOD_System_CreateSound(system, "sounds/intro.mp3", FMOD_2D | FMOD_CREATESTREAM, 0, &music);

        //Check if it well opened
        if(result != FMOD_OK) {
            fprintf(stderr, "Error: impossible to read the music file\n");
            exit(EXIT_FAILURE);
        }

        //Play the music
        FMOD_System_PlaySound(system, music, NULL, 0, &channel);

    /* Surfaces and textures */
    SDL_Surface* bg_img = NULL;
    GLuint bg_texture;

    loadSpriteArea(&bg_img, "video/INTRO_00000.png"); //Load the first image of the animation
    initSpriteTexture(&bg_img, &bg_texture);

    /* Global variables */
    int button_x = 0, button_y = 0;

    int videoFrame = 0;


	/* MAIN LOOP */
    int loop = 1;
    while(loop) 
    {
        /* Time at the beginning of the loop */
        Uint32 startTime = SDL_GetTicks();
        
        /* DRAWING CODE */

            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

	        //GET Frame
	        char frame[20] = {0};
	        char int2string[20] = {0};
	        strcat(frame, "video/INTRO_");
	            snprintf(int2string, sizeof(int2string), "%.5d", videoFrame);
	        strcat(frame, int2string);
	        strcat(frame, ".png");

	               //printf("Path = %s\n", frame);

            drawFullScreenImg(&bg_texture); //Draw each frame of the animation

            //While the animation is not over, load the new frame
            if(videoFrame != 757) {
            	videoFrame += 1;
            	loadSpriteArea(&bg_img, frame);
            	initSpriteTexture(&bg_img, &bg_texture);
            }
            else if(videoFrame >= 757) {
                FMOD_Channel_Stop(channel); //Stop the music
                playMenu(surface); //Play the menu at the end of the intro
                loop = 0; //Stop the loop
            }

        /* Update window */
        SDL_GL_SwapBuffers();
        
        /* Event loop */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                loop = 0;
                break;
            }

            switch(e.type) 
            {
                /* Resize window */
                case SDL_VIDEORESIZE:
                    reshape(&surface, e.resize.w, e.resize.h);
                    break;

                /* Mouse DOWN */
                case SDL_MOUSEBUTTONDOWN:

                    button_x = e.button.x * WINDOW_WIDTH / surface->w;
                    button_y = e.button.y * WINDOW_HEIGHT / surface->h;

                    //If mouse left button is down
                    if(e.button.button == SDL_BUTTON_LEFT) {
                    	printf("x = %d et y = %d\n", button_x, button_y);
                            
                            //If we press "Skip"
                            if(button_x > 1150 && button_x < 1200 && button_y > 20 && button_y < 40) {
                                FMOD_Channel_Stop(channel); //Stop the music
                                playMenu(surface); //Play the menu
                                loop = 0; //Stop the loop
                            }  
                    }

                    break;
            }
        }

        /* Passed time */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* If too few time, the program is paused */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }


    /* Free sprites */
    SDL_FreeSurface(bg_img);
    glDeleteTextures(1, &bg_texture);

    /* Free FMOD */
    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    /* Free SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;
}