#pragma once
#include "stdafx.h"
#include "sprites.h"
#include "Music.h"
#include "World.h"
#include "Player.h"

class CGame
{
public:
	CGame();
	~CGame();
	void gameLoop();

	//scenes
	void gameMenu();
	void gamePlay();
	void bossFight();
	void gameMenuOptions();
	void gamePlayOptions();

private:


	//scenes
	int currentScene;
	bool sceneJustSwitched;

	//game fps
	int timer;
	int fps;

	//music
	CMusic* music;

	//general for getting sprites information
	Csprites* spritesInfo;

	//text texture
	SDL_Texture* textTexture;

	/////////////////////////////
	//////////Main Menu//////////
	/////////////////////////////
	Csprites* menu_Background;
	Csprites* menu_Clouds[2];
	Csprites* menu_OilRig;
	Csprites* menu_Title;
	Csprites* menu_Start;
	Csprites* menu_Options;
	Csprites* menu_Quit;
	Csprites* menu_Pointer;

	int optionSelected;
	bool buttonPressed;

	/////////////////////////////
	//////////Game Play//////////
	/////////////////////////////
	CWorld* world;
	CPlayer* player[2];
	bool inBossFight;

	bool quit;
	CSDL_setup* sdl_Setup;

	/////////////////////////////
	///////////Options///////////
	/////////////////////////////
	Csprites* options_Lighting;
	Csprites* options_QuitToMenu;
	Csprites* options_Volume;
	Csprites* options_Back;
	Csprites* blackOut;
	bool optionAlreadySelected;
	CText* inventoryText;
};

