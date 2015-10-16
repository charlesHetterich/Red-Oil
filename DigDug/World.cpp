#include "stdafx.h"
#include "World.h"


CWorld::CWorld(CSDL_setup* csdl_Setup, int w, int h)
{
	sdl_Setup = csdl_Setup;

	width = w;
	height = h;
	
	spritesInfo = new Csprites(sdl_Setup, "images/menu/menu_Background.png", 0, 0, sdl_Setup->getScreenWidth(), sdl_Setup->getScreenHeight(), 0, 0, 500, 250);
	loadingText = new CText(sdl_Setup);
	loadingText->setColor(209, 125, 41);

	tileSet = NULL;
	tileSet = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/tileset.png");

	lightingFrequency = 100;

	//enemies
	enemiesAmount = 100;
	for (int i = 0; i < enemiesAmount; i++)
		enemy[i] = new CEnemies(sdl_Setup, i, width);

	//top background
	topBackGround = new Csprites(sdl_Setup, "images/gameplaybackground/topBackground.png", 0, -560, 3600, 600, 0, 0, 1200, 200);

	//haven background
	havenCloudsAmount = 1000;
	havenCloudTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/havenclouds.png");
	for (int i = 0; i < havenCloudsAmount; i++)
	{
		havenCloud[i] = new Csprites(sdl_Setup, " ", rand() % (width * 40), rand() % ((height * 40) / 2) + ((height * 40) / 2), 600, 200, 0, 0, 44, 12);
		havenCloud[i]->setFrameRow(rand() % 3);
		//havenCloud[i]->setAlpha(100);
	}


	//initialize all blocks and ornaments
	waterFallFrameRate = 100;
	setWorldWdith(w);
	setWorldHeight(h);

	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating World", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			block[x][y] = new CBlock(sdl_Setup, 40*x, 40*y);
			ornament[x][y] = new COrnament(sdl_Setup, 40 * x, 40 * y);
		}
	}
	
	//place top layer grass
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Top Grass", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int x = 0; x < width; x++)
		block[x][1]->setType(6);

	//place dense stone
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing dense stone", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 1000 * ((float)y / (float)height))
			{
				block[x][y]->setType(3);
			}
		}
	}

	//place iron
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Iron", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 2)
			{
				block[x][y]->setType(2);
			}
			if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
			{
				int possibleAdd = 0;
				if (block[x - 1][y - 1]->getType() == 2) possibleAdd += 200;
				if (block[x][y - 1]->getType() == 2) possibleAdd += 200;
				if (block[x + 1][y - 1]->getType() == 2) possibleAdd += 200;
				if (block[x - 1][y]->getType() == 2) possibleAdd += 200;
				if (block[x + 1][y]->getType() == 2) possibleAdd += 200;
				if (block[x - 1][y + 1]->getType() == 2) possibleAdd += 200;
				if (block[x][y + 1]->getType() == 2) possibleAdd += 200;
				if (block[x + 1][y + 1]->getType() == 2) possibleAdd += 200;

				if (randomNumber < possibleAdd)
					block[x][y]->setType(2);
			}
		}
	}

	//place copper
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Copper", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 2)
			{
				block[x][y]->setType(4);
			}
			if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
			{
				int possibleAdd = 0;
				if (block[x - 1][y - 1]->getType() == 4) possibleAdd += 150;
				if (block[x][y - 1]->getType() == 4) possibleAdd += 150;
				if (block[x + 1][y - 1]->getType() == 4) possibleAdd += 150;
				if (block[x - 1][y]->getType() == 4) possibleAdd += 150;
				if (block[x + 1][y]->getType() == 4) possibleAdd += 150;
				if (block[x - 1][y + 1]->getType() == 4) possibleAdd += 150;
				if (block[x][y + 1]->getType() == 4) possibleAdd += 150;
				if (block[x + 1][y + 1]->getType() == 4) possibleAdd += 150;

				if (randomNumber < possibleAdd)
					block[x][y]->setType(4);
			}
		}
	}

	//place copper
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Gold", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 1)
			{
				block[x][y]->setType(5);
			}
			if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
			{
				int possibleAdd = 0;
				if (block[x - 1][y - 1]->getType() == 5) possibleAdd += 150;
				if (block[x][y - 1]->getType() == 5) possibleAdd += 150;
				if (block[x + 1][y - 1]->getType() == 5) possibleAdd += 150;
				if (block[x - 1][y]->getType() == 5) possibleAdd += 150;
				if (block[x + 1][y]->getType() == 5) possibleAdd += 150;
				if (block[x - 1][y + 1]->getType() == 5) possibleAdd += 150;
				if (block[x][y + 1]->getType() == 5) possibleAdd += 150;
				if (block[x + 1][y + 1]->getType() == 5) possibleAdd += 150;

				if (randomNumber < possibleAdd)
					block[x][y]->setType(5);
			}
		}
	}

	//creating mine shafts
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating Mine Shafts", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 10000;
			if (randomNumber < 2)
			{
				int mineShaftLength = rand() % 80 + 20;
				for (int shaftY = y; shaftY < y + 5; shaftY++)
				{
					for (int shaftX = x; shaftX < x + mineShaftLength; shaftX++)
					{
						if (shaftX >= 0 && shaftX < width && shaftY >= 0 && shaftY < height)
						{
							block[shaftX][shaftY]->setType(8);
							if (shaftY == y + 1 | shaftY == y + 2 | shaftY == y + 3)
								block[shaftX][shaftY]->setType(0);
							if (shaftY == y + 1 && shaftX % 12 == 0)
								block[shaftX][shaftY]->setType(8);
							if (shaftX + 6 < width)
							{
								if (shaftY == y + 1 && (shaftX + 6) % 12 == 0)
									ornament[shaftX][shaftY]->setType(0);
							}
								
						}
					}
				}
			}
		}
	}

	//creating caves
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating Caves", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 10) 
			{
				int caveLength = rand() % 20 + 1;
				int rise = rand() % 8 + -4;
				int caveWidth = rand() % 6 + (rise + 2);
				for (int caveY = y; caveY < y + caveWidth; caveY++)
				{
					for (int caveX = x; caveX < x + caveLength / (abs(rise) + 1); caveX++)
					{
						if (caveX >= 0 && caveX < width && caveY + caveX*rise >= 0 && caveY + caveX*rise < height)
							if (rand() % 1000 < 800)
								block[caveX][caveY + caveX*rise]->setType(0);
					}
				}
			}
		}
	}

	//placing torches
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Torches", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (block[x][y]->getType() == 0)
			{
				int randomNumber = rand() % 1000;
				if (randomNumber < 10)
				{
					ornament[x][y]->setType(0);
				}
			}
		}
	}

	//creating floating islands
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating Floating Islands", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = height / 2; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			block[x][y]->setType(-1);
			ornament[x][y]->setType(-1);
		}
	}

	for (int y = height/2; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int randomNumber = rand() % 1000;
			if (randomNumber < 5)
			{
				int islandLength = rand() % 10 + 6;
				bool stillGrowing = true;

				for (int islandX = x; islandX < x + islandLength; islandX++)
				{
					if (islandX < width)
						block[islandX][y]->setType(11);
				}

				for (int islandY = y + 1; stillGrowing && islandY < height; islandY++)
				{
					for (int islandX = x; islandX < x + islandLength && islandX < width; islandX++)
					{
						int possibility = 0;
						if (islandX >= 0 && islandX < width)
						{
							if (block[islandX][islandY - 1]->getType() == 10 | block[islandX][islandY - 1]->getType() == 11)
								possibility += 300 + (sin((float)islandX*(M_PI / (float)islandLength))) * 200;
						}
						if (islandX - 1 >= 0 && islandX - 1 < width)
						{
							if ((block[islandX - 1][islandY - 1]->getType() == 10 | block[islandX - 1][islandY - 1]->getType() == 11) && (block[islandX][islandY - 1]->getType() == 10 | block[islandX][islandY - 1]->getType() == 11))
								possibility += 200 + (sin((float)islandX*(M_PI / (float)islandLength))) * 100;
						}
						if (islandX + 1 >= 0 && islandX + 1 < width)
						{
							if ((block[islandX + 1][islandY - 1]->getType() == 10 | block[islandX + 1][islandY - 1]->getType() == 11) && (block[islandX][islandY - 1]->getType() == 10 | block[islandX][islandY - 1]->getType() == 11))
								possibility += 200 + (sin((float)islandX*(M_PI/ (float)islandLength))) * 100;
						}

						if (rand() % 1000 < possibility)
						{
							block[islandX][islandY]->setType(10);
							stillGrowing = true;
						}
					}
				}
			}
		}
	}

	//adding grass
	for (int y = height / 2; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (block[x][y - 1]->getType() == -1 && block[x][y]->getType() == 10)
				block[x][y]->setType(11);
			if (block[x][y - 1]->getType() != -1 && block[x][y]->getType() == 11)
				block[x][y]->setType(10);
		}
	}

	//place shops
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Shops", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	shopsAmount = 10000;
	shopTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/shop.png");
	statsTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/stats.png");
	whiteDot = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/white_block.png");
	for (int y = 1; y < height - 3; y++)
	{
		for (int x = 1; x < width - 6; x++)
		{
			if (rand() % 1000 < 1)
			{
				shop[x][y] = new CShop(sdl_Setup, x * 40, y * 40);

				for (int borderY = y - 1; borderY < y + 4; borderY++)
				{
					for (int borderX = x - 1; borderX < x + 7; borderX++)
					{
						if (borderX == x - 1 | borderY == y - 1 | borderX == x + 6 | borderY == y + 3)
							block[borderX][borderY]->setType(1);
						else
							block[borderX][borderY]->setType(0);
					}
				}
				block[x - 1][y + 1]->setType(0);
				block[x - 1][y + 2]->setType(0);
				block[x + 6][y + 1]->setType(0);
				block[x + 6][y + 2]->setType(0);
			}
		}
	}

	//placing flowers
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Placing Flowers", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	shopsAmount = 10000;
	shopTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/shop.png");
	statsTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/stats.png");
	whiteDot = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/white_block.png");
	for (int y = height / 2; y < height - 3; y++)
	{
		for (int x = 1; x < width - 6; x++)
		{
			if (rand() % 10 < 1 && block[x][y + 1]->getType() == 11)
			{
				ornament[x][y]->setType(rand() % 3 + 1);
			}
		}
	}

	//creating bridges
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating Bridges", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = height / 2 + 1; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (block[x][y]->getType() == 11)
			{
				//check if we can make bridge
				bool isEnd = false;
				bool isSpace = true;
				for (int bridgeX = x + 1; bridgeX < 20 && isSpace && !isEnd; bridgeX++)
				{
					if (bridgeX >= 0 && bridgeX < width)
					{
						if ((block[bridgeX][y]->getType() != -1 && bridgeX - x <= 3) | (block[bridgeX][y]->getType() != -1 && block[bridgeX][y]->getType() != 11))
							isSpace = false;
						else if (block[bridgeX][y]->getType() == 11 && bridgeX - x > 3)
							isEnd = true;
					}
				}

				//creates bridge if possible
				if (isEnd)
				{
					bool doneMakingBridge = false;
					for (int bridgeX = x; !doneMakingBridge; bridgeX++)
					{
						if (bridgeX >= 0 && bridgeX < width)
						{
							if (bridgeX == x)
								ornament[bridgeX][y - 1]->setType(4);
							else if (block[bridgeX][y]->getType() == 11)
							{
								ornament[bridgeX][y - 1]->setType(5);
								doneMakingBridge = true;
							}
							else
								block[bridgeX][y]->setType(9);
						}
						else
						{
							doneMakingBridge = true;
						}
					}
				}
			}
		}
	}

	//creating waterfalls
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Generating Waterfalls", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	for (int y = height / 2 + 1; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (block[x][y]->getType() == -1 && block[x][y - 1]->getType() != -1 && rand() % 100 < 3)
			{
				bool waterFallAllowed = false;
				//check if we can make a waterfall
				for (int waterFallY = y; waterFallY < height && !waterFallAllowed; waterFallY++)
				{
					if (block[x][waterFallY]->getType() != -1)
						waterFallAllowed = true;
				}

				//create waterfall if allowed
				if (waterFallAllowed)
				{
					bool waterFallEnded = false;
					for (int waterFallY = y; !waterFallEnded; waterFallY++)
					{
						block[x][waterFallY]->setType(7);
						if (block[x][waterFallY + 1]->getType() != -1)
							waterFallEnded = true;
					}
				}
			}
		}
	}

	//fix first floor issue
	for (int x = 0; x < width; x++)
		block[x][0]->setType(-1);


	//add drops to world
	sdl_Setup->begin();

	spritesInfo->drawStatic(NULL);

	loadingText->writeCentered("fonts/western.ttf", 60, "Adding Drops", sdl_Setup->getScreenWidth() / 2, 200, NULL, NULL, NULL);

	sdl_Setup->end();
	dropsMax = 50;
	for (int i = 0; i < dropsMax; i++)
	{
		drop[i] = new CDrops(sdl_Setup);
	}
}

CWorld::~CWorld()
{
}

void CWorld::lightWorld()
{
	if (lightingFrequency + lightingTimer < SDL_GetTicks())
	{

		//reset lighting
		for (int y = ((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40) - 10; y < ((((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1) + 10; y++)
		{
			for (int x = ((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40) - 10; x < ((((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1) + 10; x++)
			{
				if (x >= 0 && x < width && y >= 0 && y < height)
				{
					block[x][y]->resetLighting();
				}
			}
		}

		//add extra lights
		if (playerX / 40 >= 0 && playerX / 40 < width && playerY / 40 >= 0 && playerY / 40 < height)
			block[playerX / 40][playerY / 40]->setLightingStrength(20);

		//actually add lighting
		for (int y = ((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40) - 10; y < ((((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1) + 10; y++)
		{
			for (int x = ((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40) - 10; x < ((((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1) + 10; x++)
			{
				if (x >= 0 && x < width && y >= 0 && y < height)
				{
					//add ornament light
					block[x][y]->setLightingStrength(block[x][y]->getLightingStrength() + ornament[x][y]->getLightingPower());

					bool checkit = false;
					if (x - 1 > 0)
						if (block[x - 1][y]->getType() != -1)
							checkit = true;
					if (x + 1 < width)
						if (block[x + 1][y]->getType() != -1)
							checkit = true;
					if (y - 1 > 0)
						if (block[x][y - 1]->getType() != -1)
							checkit = true;
					if (y + 1 < height)
						if (block[x][y + 1]->getType() != -1)
							checkit = true;

					if (block[x][y]->getLightingStrength() > 0 && checkit)
					{
						int radiusLighting = (log((double)block[x][y]->getLightingStrength()) / log(2.4))*1.5;
						float distanceApart = 0;
						for (int lightingY = y - radiusLighting; lightingY < y + radiusLighting + 1; lightingY++)
						{
							for (int lightingX = x - radiusLighting; lightingX < x + radiusLighting + 1; lightingX++)
							{
								if (lightingX >= 0 && lightingX < width && lightingY >= 0 && lightingY < height)
								{
									if (block[lightingX][lightingY]->getLightedAmount() < 255)
									{
										distanceApart = sqrt((x - lightingX) * (x - lightingX) + (y - lightingY) * (y - lightingY)) + 1;
										block[lightingX][lightingY]->addLightedAmount((255 * (float)block[x][y]->getLightingStrength()) / (pow(distanceApart, 2.4) * 7));
									}
								}
							}
						}
					}
				}
			}
		}
		lightingTimer = SDL_GetTicks();
	}
}

void CWorld::moveBackground()
{
	if (spritesInfo->getFocusY() + ((float)sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom() > (height * 40) / 2)
	{
		for (int i = 0; i < havenCloudsAmount; i++)
		{
			havenCloud[i]->setX(havenCloud[i]->getX() - 1);
			if (havenCloud[i]->getX() + havenCloud[i]->getW() < 0)
				havenCloud[i]->setX(width * 40);
		}
	}
}

void CWorld::drawWorldBackground()
{
	topBackGround->setX((float)(spritesInfo->getFocusX() - sdl_Setup->getScreenWidth() / 2) - ((float)spritesInfo->getFocusX() * (0.1)));
	topBackGround->drawObject(NULL);

	if (spritesInfo->getFocusY() + ((float)sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom() > (height * 40) / 2)
	{
		for (int i = 0; i < havenCloudsAmount; i++)
		{
			if (!(havenCloud[i]->getX() + havenCloud[i]->getW() < spritesInfo->getFocusX() - ((float)sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom() || spritesInfo->getFocusX() + ((float)sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom() < havenCloud[i]->getX() || havenCloud[i]->getY() + havenCloud[i]->getH() < spritesInfo->getFocusY() - ((float)sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom() || spritesInfo->getFocusY() + ((float)sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom() < havenCloud[i]->getY()))
				havenCloud[i]->drawObject(havenCloudTexture);
		}
	}
}

void CWorld::reArrangeCloudsForBoss()
{
	for (int i = 0; i < havenCloudsAmount; i++)
	{
		havenCloud[i]->setX(rand() % (int)((float)sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) + (playerX - ((float)sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) - havenCloud[i]->getW()/2);
		havenCloud[i]->setY(rand() % 10000 + spritesInfo->getFocusY() + (((float)sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()));
	}
}

void CWorld::moveBackgroundForBoss(float playerYVelocity)
{
	/*for (int i = 0; i < havenCloudsAmount; i++)
	{
		if (havenCloud[i]->getY() - playerY < 100)
		{
			if (havenCloud[i]->getX() + havenCloud[i]->getW() / 2 < playerX && havenCloud[i]->getX() + havenCloud[i]->getW() / 2 > playerX - 400)
			{
				havenCloud[i]->setX(havenCloud[i]->getX() - playerYVelocity);
			}
			else if (havenCloud[i]->getX() + havenCloud[i]->getW() / 2 > playerX && havenCloud[i]->getX() + havenCloud[i]->getW() / 2 < playerX + 400)
			{
				havenCloud[i]->setX(havenCloud[i]->getX() + playerYVelocity);
			}
		}
	}*/
}

void CWorld::draw()
{
	for (int y = (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40; y < (((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1; y++)
	{
		for (int x = (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40; x < (((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				if (block[x][y]->getType() != 7)
					block[x][y]->draw(tileSet);

				if (ornament[x][y]->getThereIsImage())
					ornament[x][y]->draw(tileSet);
			}
		}
	}
}

void CWorld::drawFrontWorldBlocks()
{
	//sets waterfall frame
	if (waterFallFrameRate + waterFallTimer < SDL_GetTicks())
	{
		waterFallFrame++;
		if (waterFallFrame > 4)
			waterFallFrame = 0;

		waterFallTimer = SDL_GetTicks();
	}

	for (int y = (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40; y < (((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1; y++)
	{
		for (int x = (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40; x < (((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				if (block[x][y]->getType() == 7)
				{
					block[x][y]->getBlockImage()->setFrameRow(waterFallFrame);
					block[x][y]->draw(tileSet);
				}

				block[x][y]->drawShadow(whiteDot);
			}
		}
	}
}

void CWorld::destoryBlock(int x, int y)
{
	if (block[x][y]->getType() == 2)
	{
		int amount = rand() % 3 + 1;
		for (int i = 0; i < amount; i++)
			createNewDrop(0, x * 40 + rand() % 20, y * 40 + 10);
	}

	if (block[x][y]->getType() == 4)
	{
		int amount = rand() % 3 + 1;
		for (int i = 0; i < amount; i++)
			createNewDrop(1, x * 40 + rand() % 20, y * 40 + 10);
	}

	if (block[x][y]->getType() == 5)
	{
		int amount = rand() % 2 + 1;
		for (int i = 0; i < amount; i++)
			createNewDrop(2, x * 40 + rand() % 20, y * 40 + 10);
	}

	if (ornament[x][y - 1]->getDependentOnBlockBellow())
		ornament[x][y - 1]->setType(-1);

	block[x][y]->setType(0);
}

void CWorld::createNewDrop(int type, int x, int y)
{
	bool created = false;
	for (int i = 0; i < dropsMax; i++)
	{
		if (!drop[i]->getActive() && !created)
		{
			drop[i]->setType(type);
			drop[i]->setActive(true);
			drop[i]->getImage()->setX(x);
			drop[i]->getImage()->setY(y);
			drop[i]->setVelocityX(0);
			drop[i]->setVelocityY(0);
			created = true;
		}
	}
}

void CWorld::moveDrops()
{
	for (int i = 0; i < dropsMax; i++)
	{
		if (drop[i]->getActive())
		{
			drop[i]->setVelocityY(drop[i]->getVelocityY() + 0.3);
			drop[i]->getImage()->setX(drop[i]->getImage()->getX() + drop[i]->getVelocityX());

			for (int y = drop[i]->getImage()->getY() / 40; y < (drop[i]->getImage()->getY() / 40) + 2; y++)
			{
				for (int x = drop[i]->getImage()->getX() / 40; x < (drop[i]->getImage()->getX() / 40) + 2; x++)
				{
					if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
					{
						if (!getBlock(x, y)->getPassable() && !(drop[i]->getImage()->getX() + drop[i]->getImage()->getW() <= getBlock(x, y)->getRect().x || getBlock(x, y)->getRect().x + getBlock(x, y)->getRect().w <= drop[i]->getImage()->getX() || drop[i]->getImage()->getY() + drop[i]->getImage()->getH() <= getBlock(x, y)->getRect().y || getBlock(x, y)->getRect().y + getBlock(x, y)->getRect().h <= drop[i]->getImage()->getY()))
						{
							if (drop[i]->getVelocityX() > 0) { drop[i]->getImage()->setX(getBlock(x, y)->getRect().x - drop[i]->getImage()->getW()); }
							if (drop[i]->getVelocityX() < 0) { drop[i]->getImage()->setX(getBlock(x, y)->getRect().x + getBlock(x, y)->getRect().w); }
							drop[i]->setVelocityX(0);
						}
					}
				}
			}

			/*touchingLeft = false;
			touchingRight = false;
			if (drop[i]->getImage()->getX() / 40 - 1 >= 0 && drop[i]->getImage()->getX() / 40 - 1 < getWidth() && drop[i]->getImage()->getY() / 40 >= 0 && drop[i]->getImage()->getY() / 40 < getHeight())
			{
			if (drop[i]->getImage()->getX() == getBlock(drop[i]->getImage()->getX() / 40 - 1, drop[i]->getImage()->getY() / 40)->getRect().x + getBlock(drop[i]->getImage()->getX() / 40 - 1, drop[i]->getImage()->getY() / 40)->getRect().w && !getBlock(drop[i]->getImage()->getX() / 40 - 1, drop[i]->getImage()->getY() / 40)->getPassable())
			touchingLeft = true;
			}
			if (drop[i]->getImage()->getX() / 40 + 1 >= 0 && drop[i]->getImage()->getX() / 40 + 1 < getWidth() && drop[i]->getImage()->getY() / 40 >= 0 && drop[i]->getImage()->getY() / 40 < getHeight())
			{
			if (drop[i]->getImage()->getX() + drop[i]->getImage()->getW() == getBlock(drop[i]->getImage()->getX() / 40 + 1, drop[i]->getImage()->getY() / 40)->getRect().x && !getBlock(drop[i]->getImage()->getX() / 40 + 1, drop[i]->getImage()->getY() / 40)->getPassable())
			touchingRight = true;
			}*/

			drop[i]->getImage()->setY(drop[i]->getImage()->getY() + drop[i]->getVelocityY());

			for (int y = drop[i]->getImage()->getY() / 40; y < (drop[i]->getImage()->getY() / 40) + 2; y++)
			{
				for (int x = drop[i]->getImage()->getX() / 40; x < (drop[i]->getImage()->getX() / 40) + 2; x++)
				{
					if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight())
					{
						if (!getBlock(x, y)->getPassable() && !(drop[i]->getImage()->getX() + drop[i]->getImage()->getW() <= getBlock(x, y)->getRect().x || getBlock(x, y)->getRect().x + getBlock(x, y)->getRect().w <= drop[i]->getImage()->getX() || drop[i]->getImage()->getY() + drop[i]->getImage()->getH() <= getBlock(x, y)->getRect().y || getBlock(x, y)->getRect().y + getBlock(x, y)->getRect().h <= drop[i]->getImage()->getY()))
						{
							if (drop[i]->getVelocityY() > 0)
							{
								drop[i]->getImage()->setY(getBlock(x, y)->getRect().y - drop[i]->getImage()->getH());
								if (drop[i]->getVelocityY()  > 10)
									drop[i]->setVelocityY(0);
							}
							if (drop[i]->getVelocityY() < 0)
							{
								drop[i]->getImage()->setY(getBlock(x, y)->getRect().y + getBlock(x, y)->getRect().h);
								drop[i]->setVelocityY(0);
							}
							drop[i]->setVelocityY(0);
						}
					}
				}
			}

			/*bool wasLanded = landed;
			landed = false; //makes sure to check everytime
			if ((drop[i]->getImage()->getY() / 40) + 1 < getHeight() && (drop[i]->getImage()->getY() / 40) + 1 >= 0 && drop[i]->getImage()->getX() / 40 < getWidth() && drop[i]->getImage()->getX() / 40 >= 0)
			{
			if (drop[i]->getImage()->getY() + drop[i]->getImage()->getH() == getBlock(drop[i]->getImage()->getX() / 40, (drop[i]->getImage()->getY() / 40) + 1)->getRect().y && !getBlock(drop[i]->getImage()->getX() / 40, (drop[i]->getImage()->getY() / 40) + 1)->getPassable())
			landed = true;
			}
			if ((drop[i]->getImage()->getY() / 40) + 1 < getHeight() && (drop[i]->getImage()->getY() / 40) + 1 >= 0 && drop[i]->getImage()->getX() / 40 + 1 < getWidth() && drop[i]->getImage()->getX() / 40 + 1 >= 0 && wasLanded)
			{
			if (drop[i]->getImage()->getY() + drop[i]->getImage()->getH() == getBlock(drop[i]->getImage()->getX() / 40 + 1, (drop[i]->getImage()->getY() / 40) + 1)->getRect().y && !getBlock(drop[i]->getImage()->getX() / 40 + 1, (drop[i]->getImage()->getY() / 40) + 1)->getPassable())
			landed = true;
			}
			drop[i]->move();*/
		}
	}
}

void CWorld::drawDrops()
{
	for (int i = 0; i < dropsMax; i++)
	{
		drop[i]->draw(tileSet);
	}
}

CDrops* CWorld::getDrop(int dropNumber)
{
	return drop[dropNumber];
}

void CWorld::drawShops()
{
	for (int y = (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40 - 3; y < (((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1; y++)
	{
		for (int x = (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40 - 6; x < (((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				if (getShopHere(x, y))
					shop[x][y]->drawShop(shopTexture);
			}
		}
	}
}

void CWorld::proccessShops(SDL_Rect playerRect)
{
	for (int y = (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40 - 3; y < (((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1; y++)
	{
		for (int x = (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40 - 6; x < (((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				if (getShopHere(x, y))
					if (shop[x][y]->getActive())
						shop[x][y]->proccessShop(playerRect);
			}
		}
	}
}

void CWorld::displayUpgradeAnimation()
{
	for (int y = (spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) / 40 - 3; y < (((spritesInfo->getFocusY() - (sdl_Setup->getScreenHeight() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenHeight() / spritesInfo->getZoom()) / 40) + 1; y++)
	{
		for (int x = (spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) / 40 - 6; x < (((spritesInfo->getFocusX() - (sdl_Setup->getScreenWidth() / 2) / spritesInfo->getZoom()) + sdl_Setup->getScreenWidth() / spritesInfo->getZoom()) / 40) + 1; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				if (getShopHere(x, y))
					shop[x][y]->displayUpgradeAnimation(whiteDot, statsTexture);
			}
		}
	}
}

CShop* CWorld::getShop(int x, int y)
{
	return shop[x][y];
}

int CWorld::getDropsMax()
{
	return dropsMax;
}

void CWorld::setPlayerPosition(int x, int y)
{
	playerX = x;
	playerY = y;
}

int CWorld::getWidth()
{
	return width;
}

int CWorld::getHeight()
{
	return height;
}

CBlock* CWorld::getBlock(int x, int y)
{
	return block[x][y];
}

SDL_Texture* CWorld::getTileSet()
{
	return tileSet;
}