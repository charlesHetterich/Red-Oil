#include "stdafx.h"
#include "Block.h"

int worldWidth;
int worldHeight;

CBlock::CBlock(CSDL_setup* csdl_Setup, int x, int y)
{
	sdl_Setup = csdl_Setup;
	image = new Csprites(sdl_Setup, " ", x, y, 40, 40, 0, 0, 40, 40);
	darknesssImage = new Csprites(sdl_Setup, " ", x, y, 40, 40, 0, 0, 1, 1);
	darknesssImage->setColorMod(0, 0, 0);
	darknesssImage->setAlpha(0);


	colorMod = { 255, 255, 255 };
	lightingStrength = 0;

	type = 1;
	strength = 25;
	collisionRect = { image->getX(), image->getY(), 40, 40 };
}

CBlock::~CBlock()
{
}

void CBlock::draw(SDL_Texture* tileSet)
{

	if (lightedAmount > 255)
		lightedAmount = 255;

	if (type != -1)
	{
		if (type != 0)
			image->setColorMod(colorMod.r*((float)lightedAmount / 255), colorMod.g*((float)lightedAmount / 255), colorMod.b*((float)lightedAmount / 255));

		image->drawObject(tileSet);
	}
}

void CBlock::drawShadow(SDL_Texture* whiteDot)
{
	if (type == 0)
	{
		darknesssImage->setAlpha(255 - lightedAmount);
		if (darknesssImage->getAlpha() > 0)
			darknesssImage->drawObject(whiteDot);
	}
}

void CBlock::setType(int newType)
{
	//empty air
	if (newType == -1)
	{
		type = -1;
		strength = 0;
		passable = true;
		lightingConstantStrength = 5;
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//full air
	if (newType == 0)
	{
		type = 0;
		strength = 0;
		passable = true;
		gravity = false;
		colorMod = { 50, 50, 70 };
		image->setColorMod(colorMod.r, colorMod.g, colorMod.b);
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//dead basic rock
	if (newType == 1)
	{
		type = 1;
		strength = 25;
		passable = false;
		gravity = false;
		image->setCrop(0, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//copper
	if (newType == 2)
	{
		type = 2;
		strength = 80;
		passable = false;
		gravity = false;
		image->setCrop(40, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//dense stone
	if (newType == 3)
	{
		type = 3;
		strength = 130;
		passable = false;
		gravity = false;
		image->setCrop(80, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//iron
	if (newType == 4)
	{
		type = 4;
		strength = 100;
		passable = false;
		gravity = false;
		image->setCrop(120, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//gold
	if (newType == 5)
	{
		type = 5;
		strength = 300;
		passable = false;
		gravity = false;
		image->setCrop(160, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//dead grass
	if (newType == 6)
	{
		type = 6;
		strength = 25;
		passable = false;
		gravity = false;
		image->setCrop(200, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//waterfall
	if (newType == 7)
	{
		type = 7;
		strength = 0;
		passable = true;
		gravity = false;
		image->setCrop(320, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(150);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//wood
	if (newType == 8)
	{
		type = 8;
		strength = 30;
		passable = false;
		gravity = false;
		image->setCrop(240, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//bridge
	if (newType == 9)
	{
		type = 9;
		strength = 30;
		passable = false;
		gravity = false;
		image->setCrop(280, 0, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 20};
	}

	//lively basic rock
	if (newType == 10)
	{
		type = 10;
		strength = 25;
		passable = false;
		gravity = false;
		image->setCrop(0, 40, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}

	//lively grass
	if (newType == 11)
	{
		type = 11;
		strength = 25;
		passable = false;
		gravity = false;
		image->setCrop(200, 40, 40, 40);
		colorMod = { 255, 255, 255 };
		lightingConstantStrength = 0;
		image->setAlpha(255);
		collisionRect = { image->getX(), image->getY(), 40, 40 };
	}
}

void CBlock::setCrop(int x, int y, int w, int h)
{
	image->setCrop(x, y, w, h);
}

int CBlock::getType()
{
	return type;
}

bool CBlock::getPassable()
{
	return passable;
}

bool CBlock::getGravity()
{
	return gravity;
}

int CBlock::getStrength()
{
	return strength;
}

SDL_Rect CBlock::getRect()
{
	return collisionRect;
}

void CBlock::resetLighting()
{
	lightedAmount = 0;
	lightingStrength = lightingConstantStrength;
}

float CBlock::getLightedAmount()
{
	return lightedAmount;
}

void CBlock::addLightedAmount(float newLightedAmount)
{
	if (type == 0)
		lightedAmount += 5 * newLightedAmount;
	else
		lightedAmount += newLightedAmount;
}

float CBlock::getLightingStrength()
{
	return lightingStrength;
}

void CBlock::setLightingStrength(float newLightingStrength)
{
	lightingStrength = newLightingStrength;
}

void setWorldWdith(int w)
{
	worldWidth = w;
}

void setWorldHeight(int h)
{
	worldHeight = h;
}

Csprites* CBlock::getBlockImage()
{
	return image;
}