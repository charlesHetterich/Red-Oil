#pragma once
#include "sprites.h"
#include "SDL_setup.h"
class COrnament
{
public:
	COrnament(CSDL_setup* csdl_Setup, int x, int y);
	~COrnament();

	void setType(int type);
	void draw(SDL_Texture* tileSet);
	int getType();
	float getLightingPower();
	bool getThereIsImage();
	bool getDependentOnBlockBellow();

private:

	//qualities
	float extraLightingPower;
	bool dependentOnBlockBellow;

	int type;

	//image things
	Csprites* ornamentImage;
	int ornamentFrameRate;
	int ornametFrameTimer;
	int ornamentFameAmount;
	bool thereIsImage;

	CSDL_setup* sdl_Setup;
};

