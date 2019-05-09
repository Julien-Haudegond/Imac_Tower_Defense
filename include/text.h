#ifndef TEXT_H__
#define TEXT_H__

#define MAX_TEXTS 50 //Max number of texts
#define MAX_FONTS 5 //Max number of fonts
#define MAX_COLORS 10 //Max number of colors

#define FONT_1 "Hack-Bold"

//Functions to fill
void initFontsArray(TTF_Font* fonts[]);
void initColorsArray(SDL_Color colors[]);
void fillTextsArrays(TTF_Font* fonts[], SDL_Color colors[], SDL_Surface* text_area[], GLuint text_texture[]);


//Basic functions
TTF_Font* loadFont(const char* fontName, int size);
void loadText(const char* text, TTF_Font** font, SDL_Color color, SDL_Surface** sFont, GLuint* texture);
void renderCenterText(SDL_Surface** sFont, GLuint* texture, int x , int y);
void renderLeftText(SDL_Surface** sFont, GLuint* texture, int x , int y);

#endif