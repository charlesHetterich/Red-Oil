#include "stdafx.h"
#include "SDL_setup.h"


CSDL_setup::CSDL_setup(bool* quit, int ScreenWidth, int ScreenHeight, bool bordered, bool initialyHidden)
{
	fpsRatio = 1;
	screenWidth = ScreenWidth;
	screenHeight = ScreenHeight;
	constantScreenWidth = ScreenWidth;
	constantScreenHeight = ScreenHeight;

	window = NULL;
	if (bordered) 
		window = SDL_CreateWindow("Red Oil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	else
		window = SDL_CreateWindow("Red Oil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
	if (!initialyHidden)
		SDL_ShowWindow(window);
	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}

	windowIcon = SDL_LoadBMP("images/icon.bmp");
	if (windowIcon == NULL) std::cout << "icon not loaded";
	SDL_SetWindowIcon(window, windowIcon);

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
	SDL_SetWindowMinimumSize(window, constantScreenWidth, constantScreenHeight);

}

CSDL_setup::~CSDL_setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

void CSDL_setup::updateWindow()
{
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	//SDL_SetWindowSize(window, (float)constantScreenWidth*((float)screenHeight / (float)constantScreenHeight), screenHeight);
	//SDL_GetWindowSize(window, &screenWidth, &screenHeight);

	//screenSizeZoom = (float)screenHeight / (float)constantScreenHeight;
}

SDL_Renderer* CSDL_setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_setup::GetMainEvent()
{
	return mainEvent;
}

void CSDL_setup::begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_setup::end()
{
	SDL_RenderPresent(renderer);
}

void CSDL_setup::setWindowHidden(bool hidden)
{
	if (hidden == true)
		SDL_HideWindow(window);
	else
		SDL_ShowWindow(window);
}

void CSDL_setup::setFpsRatio(float ratio)
{
	fpsRatio = ratio;
}

double CSDL_setup::getFpsRatio()
{
	return fpsRatio;
}

int CSDL_setup::getScreenWidth()
{
	return screenWidth;
}

int CSDL_setup::getScreenHeight()
{
	return screenHeight;
}

int CSDL_setup::getConstantScreenWidth()
{
	return constantScreenWidth;
}

int CSDL_setup::getConstantScreenHeight()
{
	return constantScreenHeight;
}
