#pragma once
#include "SDL_setup.h"
#include "sprites.h"

class CEnemies
{
public:
	CEnemies(CSDL_setup* csdl_Setup, int EnemyNumber, int worldWidth);
	~CEnemies();

	//generic all enemy functions
	void drawEnemy(SDL_Texture* enemyTexture);

	//spawning enemy
	void spawnEnemy(int type, int worldX, int worldY);

	//health related
	void hurtEnemy(int damage);

	//attacking
	float getStrength();

	//movement
	void moveEnemy();

private:
	//general things
	int worldWidth;

	//general enemy things
	int enemyNumber;
	int enemyType;

	//image
	Csprites* enemyImage[30];
	Csprites* attackImage[30];
	SDL_Rect enemyImgageCrop;
	SDL_Rect attackImageCrop;
	int amountOfBodyParts;
	int amountOfAttackParts;
	int runningAnimationLength;
	int enemyAttackingAnimationLength;
	int attackAnimationLength;
	int minimumFrameAttackCounts;
	int standingAnimationLength;
	bool standingAnimationTerminates;

	//attacking info
	bool seperatedAttack;
	bool bodyCollisionAttack;
	bool attacking;
	float strength;

	//movement info
	bool blockCollision;
	bool ableToFly;
	bool flying;
	float jumpSpeed;
	float jumpMaxTime;
	float jumpTimer;
	float VelocityX;
	float VelocityY;
	float maxSpeed;

	//health
	int health;
	bool alive;

	CSDL_setup* sdl_Setup;
 };