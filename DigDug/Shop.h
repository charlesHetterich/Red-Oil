#pragma once
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Text.h"
class CShop
{
public:
	CShop(CSDL_setup* csdl_Setup, int x, int y);
	~CShop();
	void drawShop(SDL_Texture* texture);
	void proccessShop(SDL_Rect playerRect);
	void displayUpgradeAnimation(SDL_Texture* flashTexture, SDL_Texture* upgradeTexture);
	void buyItem();
	bool getActive();
	int getCurrentPrice();
	int getCurrentItem();
	Csprites* getShopImage();

private:

	bool active;

	int currentPrice;
	int currentItem;
	CText* priceText;

	Csprites* upgradeFlash;
	Csprites* upgradeImage;

	Csprites* shopBackGround;
	CSDL_setup* sdl_Setup;
};

bool getShopHere(int x, int y);

int getShopPlayerIsInX();

int getShopPlayerIsInY();