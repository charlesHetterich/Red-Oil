#pragma once
#include "SDL_setup.h"
#include "sprites.h"
class CDrops
{
public:
	CDrops(CSDL_setup* csdl_Setup);
	~CDrops();
	//general
	void move();
	void draw(SDL_Texture* texture);
	void setType(int newType);
	int getType();
	void setActive(bool active);
	bool getActive();
	Csprites* getImage();
	std::string getTypeString();

	//mvoement

	void setVelocityX(float velocity);
	float getVelocityX();
	void setVelocityY(float velocity);
	float getVelocityY();

private:
	int type;

	//movement
	float velocityX;
	float velocityY;

	//image
	Csprites*oreImgage;

	//general
	bool activated;
	std::string typeString;
	
	CSDL_setup* sdl_Setup;
};

