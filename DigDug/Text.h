#pragma once
#include "SDL_setup.h"
#include "sprites.h"

class CText
{
public:
	CText(CSDL_setup* csdl_Setup);
	~CText();
	void write(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY);
	void writeObject(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY);
	void writeCentered(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY);
	void writeObjectCentered(std::string Font, int size, std::string Text, int x, int y, int w, int h, int imageY);
	void setAlpha(int newAlpha);
	void setColor(int r, int g, int b);
	int getAlpha();

private:

	SDL_Texture *texture;
	SDL_Surface *surf;

	SDL_Rect rect;
	SDL_Rect crop;

	SDL_Color Color3;
	TTF_Font *font;

	std::string fontFile;
	int fontSize;
	std::string text;

	int alpha;

	Csprites* informalSprite;
	CSDL_setup* sdl_Setup;
};

