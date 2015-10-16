#include "stdafx.h"
#include "Tools.h"


CTools::CTools(CSDL_setup* csdl_Setup)
{
	sdl_Setup = csdl_Setup;
	toolSound = new CMusic();
	toolImage = new Csprites(sdl_Setup, "image/tools.png", NULL, NULL, 21, 33, 0, 0, 7, 11);

	//stats
	type = 0;
}

CTools::~CTools()
{
}

void CTools::setType(int type)
{

}