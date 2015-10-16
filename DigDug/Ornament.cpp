#include "stdafx.h"
#include "Ornament.h"

COrnament::COrnament(CSDL_setup* csdl_Setup, int x, int y)
{
	sdl_Setup = csdl_Setup;
	ornamentImage = new Csprites(sdl_Setup, " ", x, y, 40, 40, NULL, NULL, NULL, NULL);
}

COrnament::~COrnament()
{
}

void COrnament::setType(int newType)
{
	//nothingness
	if (newType == -1)
	{
		type = -1;
		extraLightingPower = 0;
		ornamentFrameRate = 0;
		thereIsImage = false;
		dependentOnBlockBellow = false;
	}

	//torch
	if (newType == 0)
	{
		type = 0;
		extraLightingPower = 30;
		ornamentImage->setCrop(0, 160, 40, 40);
		ornamentFrameRate = 50;
		ornamentFameAmount = 8;
		thereIsImage = true;
		dependentOnBlockBellow = false;
	}

	//flower 1
	if (newType == 1)
	{
		type = 0;
		extraLightingPower = 0;
		ornamentImage->setCrop(0, 120, 40, 40);
		ornamentFrameRate = 0;
		ornamentFameAmount = 0;
		thereIsImage = true;
		dependentOnBlockBellow = true;
	}

	//flower 2
	if (newType == 2)
	{
		type = 0;
		extraLightingPower = 0;
		ornamentImage->setCrop(40, 120, 40, 40);
		ornamentFrameRate = 0;
		ornamentFameAmount = 0;
		thereIsImage = true;
		dependentOnBlockBellow = true;
	}

	//flower 3
	if (newType == 3)
	{
		type = 0;
		extraLightingPower = 0;
		ornamentImage->setCrop(80, 120, 40, 40);
		ornamentFrameRate = 0;
		ornamentFameAmount = 0;
		thereIsImage = true;
		dependentOnBlockBellow = true;
	}

	//bridge holder left side
	if (newType == 4)
	{
		type = 0;
		extraLightingPower = 0;
		ornamentImage->setCrop(120, 120, 40, 40);
		ornamentFrameRate = 0;
		ornamentFameAmount = 0;
		thereIsImage = true;
		dependentOnBlockBellow = false;
	}

	//bridge holder right side
	if (newType == 5)
	{
		type = 0;
		extraLightingPower = 0;
		ornamentImage->setCrop(160, 120, 40, 40);
		ornamentFrameRate = 0;
		ornamentFameAmount = 0;
		thereIsImage = true;
		dependentOnBlockBellow = false;
	}
}

void COrnament::draw(SDL_Texture* tileSet)
{
	if (ornamentFrameRate > 0)
	{
		if (ornamentFrameRate + ornametFrameTimer < SDL_GetTicks())
		{
			ornamentImage->setFrame(ornamentImage->getFrame() + 1);
			if (ornamentImage->getFrame() >= ornamentFameAmount)
				ornamentImage->setFrame(0);

			extraLightingPower = rand() % 10 + 20;

			ornametFrameTimer = SDL_GetTicks();
		}
	}

	ornamentImage->drawObject(tileSet);
}

int COrnament::getType()
{
	return type;
}

float COrnament::getLightingPower()
{
	return extraLightingPower;
}

bool COrnament::getThereIsImage()
{
	return thereIsImage;
}

bool COrnament::getDependentOnBlockBellow()
{
	return dependentOnBlockBellow;
}