#pragma once
#include "sprites.h"
#include "SDL_setup.h"
class CBlock
{
public:
	CBlock(CSDL_setup* csdl_Setup, int x, int y);
	~CBlock();
	void draw(SDL_Texture* tileSet);
	void drawShadow(SDL_Texture* whiteDot);
	void setCrop(int x, int y, int w, int h);
	int getType();
	bool getPassable();
	bool getGravity();
	int getStrength();
	SDL_Rect getRect();
	Csprites* getBlockImage();

	void setType(int newType);

	//lighting
	void resetLighting();
	float getLightedAmount();
	void addLightedAmount(float newLightedAmount);
	float getLightingStrength();
	void setLightingStrength(float  newLightingStrength);


	

private:
	int type;

	int strength;
	bool gravity;
	bool passable;

	//lighting
	float lightedAmount;
	float lightingStrength;
	float lightingConstantStrength;
	SDL_Color colorMod;
	Csprites* darknesssImage;

	Csprites* image;

	SDL_Rect crop;
	SDL_Rect collisionRect;

	CSDL_setup* sdl_Setup;
};

//world info
void setWorldWdith(int w);
void setWorldHeight(int h);