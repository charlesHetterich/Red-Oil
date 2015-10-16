#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"
#include "SDL_setup.h"
#include "Block.h"
#include "Ornament.h"
#include "Text.h"
#include "Drops.h"
#include "Shop.h"
#include "Enemies.h"
class CWorld
{
public:
	CWorld(CSDL_setup* csdl_Setup, int w, int h);
	~CWorld();

	//blocks
	void draw();
	void detectCollision();
	void destoryBlock(int x, int y);
	CBlock* getBlock(int x, int y);

	//drops
	void createNewDrop(int type, int x, int y);
	void moveDrops();
	void drawDrops();
	CDrops* getDrop(int dropNumber);
	int getDropsMax();

	//shops
	void drawShops();
	void proccessShops(SDL_Rect playerRect);
	void displayUpgradeAnimation();
	CShop* getShop(int x, int y);

	//lighting
	void lightWorld();
	void drawFrontWorldBlocks();

	//background
	void drawWorldBackground();
	void moveBackground();
	void reArrangeCloudsForBoss();
	void moveBackgroundForBoss(float playerYVelocity);

	//keeping track of player
	void setPlayerPosition(int x, int y);

	//general
	int getWidth();
	int getHeight();
	SDL_Texture* getTileSet();

private:

	//blocks
	CBlock* block[5000][5000];
	int width;
	int height;
	int waterFallFrameRate;
	int waterFallTimer;
	int waterFallFrame;

	//ornaments
	COrnament* ornament[5000][5000];

	//drops
	CDrops* drop[50];
	int dropsMax;

	//shops
	int shopsAmount;
	CShop* shop[5000][5000];
	SDL_Texture* shopTexture;

	//lighting
	int lightingFrequency;
	int lightingTimer;

	//top background
	Csprites* topBackGround;
	Csprites* topStarts;
	Csprites* topClouds;

	//haven background
	SDL_Texture* havenCloudTexture;
	Csprites* havenCloud[1000];
	int havenCloudsAmount;

	//enemies
	CEnemies* enemy[100];
	int enemiesAmount;
	//keeping track of player
	int playerX;
	int playerY;

	//general
	CText* loadingText;
	Csprites* spritesInfo;
	
	//textures
	SDL_Texture* statsTexture;
	SDL_Texture* whiteDot;
	SDL_Texture* tileSet;

	CSDL_setup* sdl_Setup;
};