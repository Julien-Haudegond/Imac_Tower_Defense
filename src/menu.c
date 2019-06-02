#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FMOD/fmod.h>

#include "../include/const.h"
#include "../include/menu.h"
#include "../include/game.h"

#include "../include/window.h"
#include "../include/sprite.h"
#include "../include/graphic.h"




int playMenu() {

    /* Initializing SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /*Initializing TTF */
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
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
        result = FMOD_System_CreateSound(system, "sounds/menu.mp3", FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &music);

        //Check if it well opened
        if(result != FMOD_OK) {
            fprintf(stderr, "Error: impossible to read the music file\n");
            exit(EXIT_FAILURE);
        }

        //Loop the music
        FMOD_Sound_SetLoopCount(music, -1);

        //Play the music
        FMOD_System_PlaySound(system, music, NULL, 0, &channel);

    /* Surfaces and textures */
    SDL_Surface* bg_img = NULL;
    SDL_Surface* help_img = NULL;
    SDL_Surface* choice_img = NULL;

    GLuint bg_texture;
    GLuint help_texture;
    GLuint choice_texture;

    loadSpriteArea(&bg_img, "whole_screens/Menu_Img.png");
    initSpriteTexture(&bg_img, &bg_texture);

    loadSpriteArea(&help_img, "whole_screens/Help_Img.png");
    initSpriteTexture(&help_img, &help_texture);

    loadSpriteArea(&choice_img, "whole_screens/Choice_Img.png");
    initSpriteTexture(&choice_img, &choice_texture);

    /* Global variables */
    int mouse_x = 0, mouse_y = 0, button_x = 0, button_y = 0;
    int help = -1; //Help window
    int choice = -1; //Choice window
    int map = -1; //Chosen map

    /* Global variables for GL Lists */


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

            drawFullScreenImg(&bg_texture);

            if(help == 1) {
            	drawFullScreenImg(&help_texture);
            }

            if(choice == 1) {
            	drawFullScreenImg(&choice_texture);
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
                
                /* Keyboard DOWN */
                case SDL_KEYDOWN:

                    break;

                /* Keyboard UP */
                case SDL_KEYUP:

                    break;

                /* Mouse DOWN */
                case SDL_MOUSEBUTTONDOWN:

                    button_x = e.button.x * WINDOW_WIDTH / surface->w;
                    button_y = e.button.y * WINDOW_HEIGHT / surface->h;

                    //If mouse left button is down
                    if(e.button.button == SDL_BUTTON_LEFT) {
                    	printf("x = %d et y = %d\n", button_x, button_y);

                    	//If help window is visible : become hidden
                        if(help == 1) {
                            help = -1;
                            break;
                        }

                        //If choice window is visible
                        if(choice == 1) {
                        	//Map 1
                        	if(button_x > 60 && button_x < 370 && button_y > 185 && button_y < 390) {
	                    		map = 1;
	                    	}
	                    	//Map 2
	                    	else if(button_x > 455 && button_x < 765 && button_y > 185 && button_y < 390) {
	                    		map = 2;
	                    	}
	                    	//Map 3
	                    	else if(button_x > 845 && button_x < 1150 && button_y > 185 && button_y < 390) {
	                    		map = 3;
	                    	}
	                    	//Map 4
	                    	else if(button_x > 260 && button_x < 570 && button_y > 445 && button_y < 650) {
	                    		map = 4;
	                    	}
	                    	//Map 5
	                    	else if(button_x > 650 && button_x < 930 && button_y > 445 && button_y < 650) {
	                    		map = 5;
	                    	}
	                    	//Back
	                    	else if(button_x > 60 && button_x < 180 && button_y > 725 && button_y < 755) {
	                    		choice = -1;
	                    	}

	                    	if(map != -1) {
						        //GET ITD relative path
						        char itdMap[20] = {0};
						        char int2string[2] = {0};
						        strcat(itdMap, "data/Map_0");
						            snprintf(int2string, sizeof(int2string), "%d", map);
						        strcat(itdMap, int2string);
						        strcat(itdMap, ".itd");

						        printf("Path = %s\n", itdMap);

						        //Play the game
	                    		FMOD_Channel_Stop(channel); //Stop the music
	                    		playGame(surface, itdMap); //Play the game

	                    		//Go back to the menu
	                    		initSpriteTexture(&bg_img, &bg_texture); //Reload the menu texture
	                    		initSpriteTexture(&help_img, &help_texture); //Reload the help texture
	                    		initSpriteTexture(&choice_img, &choice_texture); //Reload the choice texture

	                    		FMOD_System_PlaySound(system, music, NULL, 0, &channel); //Play the music

	                    		map = -1; //Reset map
	                    		choice = -1; //Hide the choice window

	                    	}                    	
                        }

                        if(help == -1 && choice == -1) {
	                    	//If we press "Play game"
	                    	if(button_x > 375 && button_x < 845 && button_y > 450 && button_y < 500 && choice == -1) {
	                    		choice = 1;
	                    	}

	                    	//If we press "Help"
	                    	if(button_x > 500 && button_x < 700 && button_y > 550 && button_y < 600) {
	                    		help = 1;
	                    	}     

	                    	//If we press "Exit"
	                    	if(button_x > 525 && button_x < 700 && button_y > 650 && button_y < 700) {
	                    		loop = 0;
	                    	}                          	
                        }  
                    }


                    //If mouse right button is down
                    if(e.button.button == SDL_BUTTON_RIGHT) {

                    }

                    break;


                case SDL_MOUSEBUTTONUP:

                    //If mouse right button is up
                    if(e.button.button == SDL_BUTTON_RIGHT) {

                    }   
                    
                default:
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

    SDL_FreeSurface(help_img);
    glDeleteTextures(1, &help_texture);

    SDL_FreeSurface(choice_img);
    glDeleteTextures(1, &choice_texture);

    /* Free FMOD */
    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    /* Free TTF */
    TTF_Quit();

    /* Free SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;

}