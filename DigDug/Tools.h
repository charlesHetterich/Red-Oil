#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"

class CTools
{
public:
	CTools(CSDL_setup* csdl_Setup);
	~CTools();
	void drawTool();
	void setType(int type);

private:
	int type;

	//tool stats
	int groundStrength;
	int enemyStrength;
	int knockBack;

	//general
	Csprites* toolImage;
	CMusic* toolSound;
	CSDL_setup* sdl_Setup;
};

