#include "stdafx.h"
#include "Drops.h"


CDrops::CDrops(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	oreImgage = new Csprites(sdl_Setup, " ", NULL, NULL, 16, 13, 40, 40, 11, 9);
}

CDrops::~CDrops()
{
}

void CDrops::move()
{
	oreImgage->setX(oreImgage->getX() + velocityX);
	oreImgage->setY(oreImgage->getY() + velocityY);
}

void CDrops::draw(SDL_Texture* texture)
{
	if (activated)
	{
		oreImgage->drawObject(texture);
	}
}

void CDrops::setType(int newType)
{
	if (newType == 0)
	{
		type = 0;
		oreImgage->setCrop(40, 40, 11, 9);
		typeString = "iron";
	}

	if (newType == 1)
	{
		type = 1;
		oreImgage->setCrop(120, 40, 11, 9);
		typeString = "copper";
	}

	if (newType == 2)
	{
		type = 2;
		oreImgage->setCrop(160, 40, 11, 9);
		typeString = "gold";
	}

}

int CDrops::getType()
{
	return type;
}

void CDrops::setActive(bool active)
{
	activated = active;
}

bool CDrops::getActive()
{
	return activated;
}

Csprites* CDrops::getImage()
{
	return oreImgage;
}

void CDrops::setVelocityX(float velocity)
{
	velocityX = velocity;
}

float CDrops::getVelocityX()
{
	return velocityX;
}

void CDrops::setVelocityY(float velocity)
{
	velocityY = velocity;
}

float CDrops::getVelocityY()
{
	return velocityY;
}

std::string CDrops::getTypeString()
{
	return typeString;
}