#ifndef TEXT_H__
#define TEXT_H__

#define MAX_TEXTS 50 //Max number of texts
#define MAX_CSS 5 //Max number of text styles

#define FONT_1 "Hack-Bold"

typedef struct TextStyle {
	TTF_Font* font;
	SDL_Color color;
} TextStyle;

typedef struct Text {
	SDL_Surface* area;
	GLuint texture;
} Text;

//Init and free
void initTextCSSToNull(TextStyle textCSS[]);
void freeTextCSS(TextStyle textCSS[]);
void initTextsToNull(Text texts[]);
void freeTexts(Text texts[]);

//Functions to fill
void initTextCSS(TextStyle textCSS[]);
void fillTextsArrays(TextStyle textCSS[], Text texts[]);


//Basic functions
TTF_Font* loadFont(const char* fontName, int size);
void loadText(const char* text, TTF_Font** font, SDL_Color color, SDL_Surface** sFont, GLuint* texture);
void renderCenterText(Text* text, int x , int y);
void renderLeftText(Text* text, int x , int y);
void renderRightText(Text* text, int x , int y);

void loadIntegerText(int integer, TextStyle* textCSS, Text* text);

#endif