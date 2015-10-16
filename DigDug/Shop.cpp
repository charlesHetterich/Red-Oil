#include "stdafx.h"
#include "Shop.h"

bool shopHere[5000][5000];
int pickAxePrice = 10;
int healthPrice = 50;
int moneyPrice = 1000;

int shopPlayerInX = -1;
int shopPlayerInY;

CShop::CShop(CSDL_setup* csdl_Setup, int x, int y)
{
	sdl_Setup = csdl_Setup;
	shopBackGround = new Csprites(sdl_Setup, " ", x, y, 240, 120, 0, 0, 80, 40);
	shopBackGround->setColorMod(255, 255, 255);

	upgradeFlash = new Csprites(sdl_Setup, " ", x, y, 240, 120, 0, 0, 1, 1);
	upgradeFlash->setAlpha(0);
	upgradeImage = new Csprites(sdl_Setup, " ", x + 70, y + 10, 100, 100, 0, 11, 11, 11);
	upgradeImage->setAlpha(0);
	
	priceText = new CText(sdl_Setup);

	shopHere[x/40][y/40] = true;

	active = true;
}

CShop::~CShop()
{
}

void CShop::drawShop(SDL_Texture* texture)
{
	shopBackGround->drawObject(texture);
	if (currentPrice > 0)
	{
		std::string priceString = "$" + std::to_string(currentPrice);
		priceText->writeObjectCentered("fonts/tinyFill.ttf", 10, priceString, shopBackGround->getX() + shopBackGround->getW()/2, shopBackGround->getY() + 95, NULL, NULL, NULL);
	}
	currentPrice = 0;
}

void CShop::proccessShop(SDL_Rect playerRect)
{
	if (!(playerRect.y + playerRect.h < shopBackGround->getY() || shopBackGround->getY() + shopBackGround->getH() < playerRect.y))
	{
		if (playerRect.x < shopBackGround->getX() + 60 && playerRect.x + playerRect.w > shopBackGround->getX() + 60)
		{
			currentPrice = pickAxePrice;
			currentItem = 0;
			shopPlayerInX = shopBackGround->getX() / 40;
			shopPlayerInY = shopBackGround->getY() / 40;
			upgradeImage->setCrop(0, 11, 11, 11);
		}
		else if (playerRect.x < shopBackGround->getX() + 120 && playerRect.x + playerRect.w > shopBackGround->getX() + 120)
		{
			currentPrice = healthPrice;
			currentItem = 1;
			shopPlayerInX = shopBackGround->getX() / 40;
			shopPlayerInY = shopBackGround->getY() / 40;
			upgradeImage->setCrop(11, 11, 11, 11);
		}
		else if (playerRect.x < shopBackGround->getX() + 180 && playerRect.x + playerRect.w > shopBackGround->getX() + 180)
		{
			currentPrice = moneyPrice;
			currentItem = 2;
			shopPlayerInX = shopBackGround->getX() / 40;
			shopPlayerInY = shopBackGround->getY() / 40;
			upgradeImage->setCrop(22, 11, 11, 11);
		}
	}
}

bool CShop::getActive()
{
	return active;
}

int CShop::getCurrentPrice()
{
	return currentPrice;
}

int CShop::getCurrentItem()
{
	return currentItem;
}

void CShop::buyItem()
{
	shopBackGround->setCrop(0, 40, 80, 40);
	upgradeFlash->setAlpha(255);
	upgradeImage->setAlpha(255);
	active = false;
}

void CShop::displayUpgradeAnimation(SDL_Texture* flashTexture, SDL_Texture* upgradeTexture)
{
	if (upgradeFlash->getAlpha() > 0)
	{
		std::cout << upgradeFlash->getAlpha() << "\n";
		upgradeFlash->setAlpha(upgradeFlash->getAlpha() - 5);
		upgradeImage->setAlpha(upgradeImage->getAlpha() - 5);

		upgradeFlash->drawObject(flashTexture);
		upgradeImage->drawObject(upgradeTexture);


	}
}

Csprites* CShop::getShopImage()
{
	return shopBackGround;
}

bool getShopHere(int x, int y)
{
	if (shopHere[x][y])
		return true;
	else
		return false;
}

int getShopPlayerIsInX()
{
	return shopPlayerInX;
}

int getShopPlayerIsInY()
{
	return shopPlayerInY;
}