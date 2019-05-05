#ifndef CONST_H__
#define CONST_H__


/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 30.;
static const float GL_VIEW_HEIGHT = 20.;

/* Taille d'un bloc */
static const float GL_SPRITE_SIZE = 41.;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1230; //GL_VIEW_WIDTH * GL_SPRITE
static const unsigned int WINDOW_HEIGHT = 820; //GL_VIEW_HEIGHT * GL_SPRITE
static const char WINDOW_TITLE[] = "Test_Draw";

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


#endif