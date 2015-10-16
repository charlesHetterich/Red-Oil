#include "stdafx.h"
#include "Enemies.h"


/********************************************************************************************************************************************************
//////////////////////////////////////////////////////////////GENERAL ENEMIES////////////////////////////////////////////////////////////////////////////
********************************************************************************************************************************************************/
CEnemies::CEnemies(CSDL_setup* csdl_Setup, int EnemyNumber, int widthOfWorld)
{
	sdl_Setup = csdl_Setup;
	enemyNumber = EnemyNumber;
	worldWidth = widthOfWorld;

	for (int i = 0; i < 30; i++)
	{
		enemyImage[i] = new Csprites(sdl_Setup, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		attackImage[i] = new Csprites(sdl_Setup, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	}
}

CEnemies::~CEnemies()
{
}

void CEnemies::spawnEnemy(int type, int worldX, int worldY)
{
	//mushroom monster
	if (type == 0)
	{
		enemyType = 0;

		//image
		enemyImage[0]->setW(30);
		enemyImage[0]->setH(30);
		attackImage[0]->setW(60);
		attackImage[0]->setH(20);
		enemyImgageCrop = {0, 0, 27, 18};
		enemyImage[0]->setCrop(0, 0, 27, 18);
		attackImageCrop = {0, 54, 40, 18};
		attackImage[0]->setCrop(0, 54, 40, 18);
		amountOfBodyParts = 1;
		amountOfAttackParts = 1;
		runningAnimationLength = 8;
		enemyAttackingAnimationLength = 8;
		attackAnimationLength = 8;
		minimumFrameAttackCounts = 4;
		standingAnimationLength = 3;
		standingAnimationTerminates = true;

		//attacking info
		seperatedAttack = true;
		bodyCollisionAttack = false;
		strength = 5;

		//movement info
		blockCollision = true;
		ableToFly = false;
		jumpSpeed = 5;
		jumpMaxTime = 20;
		maxSpeed = 4;

		//health
		health = 20;
		alive = true;
	}
}

void CEnemies::drawEnemy(SDL_Texture* enemyTexture)
{
	if (alive)
	{
		//setting animations
		if (attacking)

		for (int i = 0; i < amountOfBodyParts; i++)
			enemyImage[i]->drawObject(enemyTexture);

		if (attacking)
		{
			for (int i = 0; i < amountOfBodyParts; i++)
				attackImage[i]->drawObject(enemyTexture);
		}
	}
}

void CEnemies::hurtEnemy(int damage)
{
	health -= damage;

	if (health < 0)
		alive = false;
}

void CEnemies::moveEnemy()
{

}