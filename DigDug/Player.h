#pragma once
#include "SDL_setup.h"
#include "sprites.h"
#include "Music.h"
#include "World.h"
class CPlayer
{
public:
	CPlayer(CSDL_setup* csdl_Setup, CWorld* theWorld, int controlsInput);
	~CPlayer();
	void draw();
	void drawShot();
	void displayStats();
	void displayInventory();
	void takeDamage(int damageAmount);
	void move();
	void dig();
	void shootGun();
	void pickUpDrops();
	void buyUpgrades();
	void lockPlayer(bool locked);
	void setPlayerXVelocity(float newVelocity);
	float getPlayerYVelocity();
	Csprites* getImage();

private:

	int input;

	//moving
	bool playerLocked;
	int jumpedLast; //timer
	int jumpMaxDurration;
	int jumpDurration;
	bool jumped;
	float velocityX;
	float velocityY;
	bool landed;
	bool touchingLeft;
	bool touchingRight;
	float gravity;
	bool facingLeft;

	//breaking
	Csprites* breakingImage;
	bool breaking;
	int damageDone;
	int breakingX;
	int breakingY;
	int lastBreakingX;
	int lastBreakingY;

	//shooting
	bool shooting;
	bool shot;
	Csprites* shotImage;

	//image things
	SDL_Texture* playerTexture;
	Csprites* image;
	Csprites* extraAnimationSpace;
	int runningFrameSpeed;
	int runningTimer;
	int miningFrameSpeed;
	int miningTimer;
	int shootingFrameSpeed;
	int shootingTimer;

	//health
	Csprites* healthBar;
	Csprites* emptyHealthBar;
	CText* dealtText;
	std::string dealtString;
	float health;
	float maxHealth;

	//money
	int money;
	CText* moneyText;

	//stats
	SDL_Texture* statsTexture;
	CText* statsText[3];
	Csprites* pickaxeStatsPicture;
	Csprites* healthStatsPicutre;
	Csprites* moneyStatsPicture;
	int pickaxeLevel;
	int healthLevel;
	int moneyLevel;

	//inventory
	CText* pickUpText;
	CText* inventoryText;
	std::string pickUpString;
	Csprites* oreImage[10];
	int ironCount;
	int copperCount;
	int goldCount;

	//general
	CMusic* playerSounds;
	CWorld* world;
	CSDL_setup* sdl_Setup;
};

