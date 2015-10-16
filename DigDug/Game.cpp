#include "stdafx.h"
#include "Game.h"


CGame::CGame()
{
	
	srand(time(NULL));
	quit = false;
	sdl_Setup = new CSDL_setup(&quit, 1500, 750, true, false);
	fps = 60;
	initializeGamePad(sdl_Setup);
	spritesInfo = new Csprites(sdl_Setup, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	textTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/text.png");
	SDL_SetRenderDrawColor(sdl_Setup->GetRenderer(), 88, 140, 243, 255);

	/////////////////////////////
	//////////Main Menu//////////
	/////////////////////////////
	menu_Background = new Csprites(sdl_Setup, "images/menu/menu_Background.png", 0, 0, sdl_Setup->getScreenWidth(), sdl_Setup->getScreenHeight(), 0, 0, 500, 250);
	menu_Clouds[0] = new Csprites(sdl_Setup, "images/menu/menu_clouds.png", 0, 50, 1245, 202, 0, 0, 166, 27);
	menu_Clouds[0]->setAlpha(150);
	menu_Clouds[1] = new Csprites(sdl_Setup, "images/menu/menu_clouds.png", 1345, 50, 1245, 202, 0, 0, 166, 27);
	menu_Clouds[1]->setAlpha(150);
	menu_OilRig = new Csprites(sdl_Setup, "images/menu/menu_oilrig.png", 1100, -23, 375, 375, 0, 0, 50, 50);
	menu_Start = new Csprites(sdl_Setup, " ", 600, 350, 292, 60, 0, 78, 39, 8);
	menu_Options = new Csprites(sdl_Setup, " ", 550, 450, 397, 60, 0, 13, 82, 13);
	menu_Title = new Csprites(sdl_Setup, " ", 500, 100, 562, 97, 0, 65, 75, 13);
	menu_Quit = new Csprites(sdl_Setup, " ", 635, 550, 217, 60, 0, 52, 45, 13);
	menu_Pointer = new Csprites(sdl_Setup, "images/menu/menu_Pointer.png", 430, 340, 127, 157, 0, 0, 17, 21);

	/////////////////////////////
	//////////Game Play//////////
	/////////////////////////////

	/////////////////////////////
	///////////Options///////////
	/////////////////////////////
	blackOut = new Csprites(sdl_Setup, "images/white_block.png", 0, 0, sdl_Setup->getScreenWidth(), sdl_Setup->getScreenHeight(), 0, 0, 1, 1);
	blackOut->setColorMod(0, 0, 0);
	blackOut->setAlpha(150);
	inventoryText = new CText(sdl_Setup);
	options_Lighting = new Csprites(sdl_Setup, " ", 535, 450, 430, 60, 0, 26, 89, 13);
	options_QuitToMenu = new Csprites(sdl_Setup, " ", 300, 550, 900, 60, 0, 39, 186, 13);
	options_Volume = new Csprites(sdl_Setup, " ", 570, 350, 363, 60, 0, 0, 75, 13);
	
	music = new CMusic();
	music->fadeInMusic(0, -1, 1000);
	
	timer = SDL_GetTicks();
}

CGame::~CGame()
{
	delete sdl_Setup;
}

void CGame::gameLoop()
{
	while (!quit && sdl_Setup->GetMainEvent()->type != SDL_QUIT)
	{
		updateButtons();
		if (timer + (1000 / fps) < SDL_GetTicks())
		{
			sdl_Setup->updateWindow();
			spritesInfo->setWindowSizeZoom();

			sdl_Setup->begin();

			//scenes
			if (currentScene == 0) { gameMenu(); }
			else if (currentScene == 1) { gamePlay(); }
			else if (currentScene == 2) { gamePlayOptions(); }
			else if (currentScene == 3) { gameMenuOptions(); }
			else if (currentScene == 4) { bossFight(); }

			sdl_Setup->end();

			if (getPressed(0, 8))
				spritesInfo->takeScreenShot();
			
			timer = SDL_GetTicks();
		}
	}
}

void CGame::gameMenu()
{
	//inputs
	if (getPressed(0,2) && !buttonPressed) { optionSelected--; buttonPressed = true; music->playSound(0); }
	if (getPressed(0,3) && !buttonPressed) { optionSelected++; buttonPressed = true; music->playSound(0); }
	if (!getPressed(0,2) && !getPressed(0,3))
		buttonPressed = false;

	if (optionSelected > 2)
		optionSelected = 0;
	else if (optionSelected == -1)
		optionSelected = 2;

	if (getPressed(0, 4))
	{
		if (!optionAlreadySelected)
		{
			optionAlreadySelected = true;
			if (optionSelected == 0)
			{
				currentScene = 1;
				optionAlreadySelected = true;
				if (!world)
				{
					world = new CWorld(sdl_Setup, 500, 2000);

					player[0] = new CPlayer(sdl_Setup, world, 0);
					player[1] = new CPlayer(sdl_Setup, world, 1);
				}
			}
			else if (optionSelected == 1)
			{
				currentScene = 3;
				optionSelected = 0;
				optionAlreadySelected = true;
			}
			else if (optionSelected == 2)
			{
				quit = true;
			}
		}
	}
	else
		optionAlreadySelected = false;

	//move
	if (optionSelected == 0)
	{
		menu_Pointer->setX(430);
		menu_Pointer->setY(290);
	}
	else if (optionSelected == 1)
	{
		menu_Pointer->setX(380);
		menu_Pointer->setY(390);
	}
	else if (optionSelected == 2)
	{
		menu_Pointer->setX(445);
		menu_Pointer->setY(490);
	}
	for (int x = 0; x < 2; x++)
	{
		menu_Clouds[x]->setX(menu_Clouds[x]->getX() - 1);
		if (menu_Clouds[x]->getX() + menu_Clouds[x]->getW() < 0)
			menu_Clouds[x]->setX(sdl_Setup->getScreenWidth());
	}

	//draw
	menu_Background->drawStatic(NULL);
	menu_Clouds[0]->drawStatic(NULL);
	menu_Clouds[1]->drawStatic(NULL);
	menu_OilRig->drawStatic(NULL);
	menu_Title->drawStatic(textTexture);
	menu_Start->drawStatic(textTexture);
	menu_Options->drawStatic(textTexture);
	menu_Quit->drawStatic(textTexture);
	menu_Pointer->drawStatic(NULL);
}

void CGame::gamePlay()
{
	//switch to inventory
	if (getPressed(0, 5) && !optionAlreadySelected)
	{
		currentScene = 2;
		optionAlreadySelected = true;
		optionSelected = 0;
	}
	else if (!getPressed(0, 5))
		optionAlreadySelected = false;

	//transition to boss fight
	if (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom() > world->getHeight() * 40)
	{
		currentScene = 4;
		int playerDistanceFromNewArea = 1000 - player[0]->getImage()->getX();
		player[0]->getImage()->setX(1000);
		player[0]->lockPlayer(true);
		player[0]->setPlayerXVelocity(0);
		world->setPlayerPosition(player[0]->getImage()->getX(), player[0]->getImage()->getY());
		spritesInfo->setFocusX(spritesInfo->getFocusX() + playerDistanceFromNewArea);
		world->reArrangeCloudsForBoss();
	}

	//movement
	player[0]->move();
	world->moveBackground();
	world->moveDrops();

	//change things
	player[0]->dig();
	player[0]->shootGun();
	player[0]->pickUpDrops();
	world->proccessShops(player[0]->getImage()->getRect());
	player[0]->buyUpgrades();
	world->lightWorld();

	//set camera view
	spritesInfo->setFocusX(player[0]->getImage()->getFocusX() + ((player[0]->getImage()->getX() + player[0]->getImage()->getW() / 2) - player[0]->getImage()->getFocusX()) / 10);
	spritesInfo->setFocusY(player[0]->getImage()->getFocusY() + ((player[0]->getImage()->getY() + player[0]->getImage()->getH() / 2) - player[0]->getImage()->getFocusY()) / 10);
	if (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / player[0]->getImage()->getZoom() < 0)
		spritesInfo->setFocusX(sdl_Setup->getScreenWidth() / 2 / player[0]->getImage()->getZoom());
	if (spritesInfo->getFocusX() + (sdl_Setup->getScreenWidth() / 2) / player[0]->getImage()->getZoom() > world->getWidth() * 40)
		spritesInfo->setFocusX(world->getWidth() * 40 - sdl_Setup->getScreenWidth() / 2 / player[0]->getImage()->getZoom());

	//draw
	//object oriented
	world->drawWorldBackground();
	world->draw();
	world->drawShops();
	world->drawDrops();
	player[0]->draw();
	player[0]->drawShot();
	world->drawFrontWorldBlocks();

	//static oriented
	world->displayUpgradeAnimation();
	player[0]->displayStats();
}

void CGame::bossFight()
{
	//switch to inventory
	if (getPressed(0, 5) && !optionAlreadySelected)
	{
		currentScene = 2;
		optionAlreadySelected = true;
		optionSelected = 0;
	}
	else if (!getPressed(0, 5))
		optionAlreadySelected = false;

	//movement
	player[0]->move();
	//world->moveBackgroundForBoss(player[0]->getPlayerYVelocity());

	spritesInfo->setZoom(10);
	spritesInfo->setFocusX(player[0]->getImage()->getX() + player[0]->getImage()->getW() / 2);
	spritesInfo->setFocusY(player[0]->getImage()->getY() + player[0]->getImage()->getH() / 2);

	//change things
	player[0]->shootGun();

	//set camera view
	player[0]->getImage()->setFocusX(player[0]->getImage()->getFocusX() + ((player[0]->getImage()->getX() + player[0]->getImage()->getW() / 2) - player[0]->getImage()->getFocusX()) / 10);
	player[0]->getImage()->setFocusY(player[0]->getImage()->getFocusY() + ((player[0]->getImage()->getY() + player[0]->getImage()->getH() / 2) - player[0]->getImage()->getFocusY()) / 10);
	if (player[0]->getImage()->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / player[0]->getImage()->getZoom() < 0)
		player[0]->getImage()->setFocusX(sdl_Setup->getScreenWidth() / 2 / player[0]->getImage()->getZoom());
	if (player[0]->getImage()->getFocusX() + (sdl_Setup->getScreenWidth() / 2) / player[0]->getImage()->getZoom() > world->getWidth() * 40)
		player[0]->getImage()->setFocusX(world->getWidth() * 40 - sdl_Setup->getScreenWidth() / 2 / player[0]->getImage()->getZoom());

	//draw
	//object oriented
	player[0]->draw();
	player[0]->drawShot();
	world->drawWorldBackground();

	//static oriented
	world->displayUpgradeAnimation();
	player[0]->displayStats();
}

void CGame::gamePlayOptions()
{
	//inputs
	if (getPressed(0, 2) && !buttonPressed) { optionSelected--; buttonPressed = true; music->playSound(0); }
	if (getPressed(0, 3) && !buttonPressed) { optionSelected++; buttonPressed = true; music->playSound(0); }
	if (!getPressed(0, 2) && !getPressed(0, 3))
		buttonPressed = false;

	if (optionSelected > 2)
		optionSelected = 0;
	else if (optionSelected == -1)
		optionSelected = 2;

	if (getPressed(0, 4))
	{
		if (!optionAlreadySelected)
		{
			if (optionSelected == 0)
			{
			}
			else if (optionSelected == 1)
			{
			}
			else if (optionSelected == 2)
			{
				currentScene = 0;
				optionSelected = 0;
				optionAlreadySelected = true;
			}
		}
	}
	else if (getPressed(0, 5))
	{
		if (!optionAlreadySelected)
		{
			optionAlreadySelected = true;
			if (!inBossFight)
				currentScene = 1;
			else if (inBossFight)
				currentScene = 4;
		}
	}
	else
		optionAlreadySelected = false;

	//move
	if (optionSelected == 0)
	{
		menu_Pointer->setX(400);
		menu_Pointer->setY(290);
	}
	else if (optionSelected == 1)
	{
		menu_Pointer->setX(365);
		menu_Pointer->setY(390);
	}
	else if (optionSelected == 2)
	{
		menu_Pointer->setX(130);
		menu_Pointer->setY(490);
	}

	//draw
	//object oriented
	world->drawWorldBackground();
	world->draw();
	world->drawShops();
	world->drawDrops();
	player[0]->draw();
	player[0]->drawShot();
	world->drawFrontWorldBlocks();

	//static oriented
	world->displayUpgradeAnimation();
	player[0]->displayStats();

	options_Volume->drawStatic(textTexture);
	options_Lighting->drawStatic(textTexture);
	options_QuitToMenu->drawStatic(textTexture);
	menu_Pointer->drawStatic(NULL);
}

void CGame::gameMenuOptions()
{
	//inputs
	if (getPressed(0, 2) && !buttonPressed) { optionSelected--; buttonPressed = true; music->playSound(0); }
	if (getPressed(0, 3) && !buttonPressed) { optionSelected++; buttonPressed = true; music->playSound(0); }
	if (!getPressed(0, 2) && !getPressed(0, 3))
		buttonPressed = false;

	if (optionSelected > 2)
		optionSelected = 0;
	else if (optionSelected == -1)
		optionSelected = 2;

	if (getPressed(0, 4))
	{
		if (!optionAlreadySelected)
		{
			if (optionSelected == 0)
			{
			}
			else if (optionSelected == 1)
			{
			}
			else if (optionSelected == 2)
			{
				currentScene = 0;
				optionSelected = 0;
				optionAlreadySelected = true;
			}
		}
	}
	else
		optionAlreadySelected = false;

	//move
	if (optionSelected == 0)
	{
		menu_Pointer->setX(400);
		menu_Pointer->setY(290);
	}
	else if (optionSelected == 1)
	{
		menu_Pointer->setX(365);
		menu_Pointer->setY(390);
	}
	else if (optionSelected == 2)
	{
		menu_Pointer->setX(130);
		menu_Pointer->setY(490);
	}

	for (int x = 0; x < 2; x++)
	{
		menu_Clouds[x]->setX(menu_Clouds[x]->getX() - 1);
		if (menu_Clouds[x]->getX() + menu_Clouds[x]->getW() < 0)
			menu_Clouds[x]->setX(sdl_Setup->getScreenWidth());
	}

	//draw
	menu_Background->drawStatic(NULL);
	menu_Clouds[0]->drawStatic(NULL);
	menu_Clouds[1]->drawStatic(NULL);
	options_Volume->drawStatic(textTexture);
	options_Lighting->drawStatic(textTexture);
	options_QuitToMenu->drawStatic(textTexture);
	menu_Pointer->drawStatic(NULL);
}