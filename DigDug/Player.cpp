#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer(CSDL_setup* csdl_Setup, CWorld* theWorld, int controlsInput)
{
	//general things
	sdl_Setup = csdl_Setup;
	world = theWorld;
	input = controlsInput;
	playerSounds = new CMusic();

	//player things
	playerTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/miner.png");
	image = new Csprites(sdl_Setup, " ", 0, -100, 24, 35, 0, 0, 13, 22);
	extraAnimationSpace = new Csprites(sdl_Setup, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	image->setFrameRow(controlsInput);
	jumpMaxDurration = 20;

	gravity = 0.25;

	//health
	maxHealth = 100;
	health = maxHealth;
	emptyHealthBar = new Csprites(sdl_Setup, "images/health.png", 30, 30, 76, 74, 38, 0, 38, 37);
	healthBar = new Csprites(sdl_Setup, "images/health.png", 30, 30, 76, 74, 0, 0, 38, 37);
	dealtText = new CText(sdl_Setup);
	dealtText->setAlpha(0);

	//money
	moneyText = new CText(sdl_Setup);
	moneyText->setColor(255, 188, 0);

	//stats
	statsTexture = IMG_LoadTexture(sdl_Setup->GetRenderer(), "images/stats.png");
	for (int i = 0; i < 3; i++)
		statsText[i] = new CText(sdl_Setup);
	pickaxeStatsPicture = new Csprites(sdl_Setup, " ", 150, 15, 100, 100, 0, 0, 11, 11);
	healthStatsPicutre = new Csprites(sdl_Setup, " ", 300, 15, 100, 100, 11, 0, 11, 11);
	moneyStatsPicture = new Csprites(sdl_Setup, " ", 450, 15, 100, 100, 22, 0, 11, 11);

	//inventory
	pickUpText = new CText(sdl_Setup);
	inventoryText = new CText(sdl_Setup);
	pickUpText->setColor(215, 163, 58);
	pickUpText->setAlpha(0);
	oreImage[0] = new Csprites(sdl_Setup, " ", 50, 200, 16, 13, 40, 40, 11, 9);
	oreImage[1] = new Csprites(sdl_Setup, " ", 50, 250, 16, 13, 120, 40, 11, 9);
	oreImage[2] = new Csprites(sdl_Setup, " ", 50, 300, 16, 13, 160, 40, 11, 9);

	//mining image
	breakingImage = new Csprites(sdl_Setup, "images/breaking.png", 0, 0, 40, 40, 0, 0, 16, 16);

	//shooting
	shotImage = new Csprites(sdl_Setup, "images/white_block.png", 0, 0, 2000, 5, 0, 0, 1, 1);
	shotImage->setAlpha(0);
	
	
	//image things
	miningFrameSpeed = 70;
	shootingFrameSpeed = 50;
}

CPlayer::~CPlayer()
{
}

void CPlayer::draw()
{
	//correctly display direction player is facing
	if (velocityX > 0)
	{
		image->setFlip(SDL_FLIP_NONE);
		extraAnimationSpace->setFlip(SDL_FLIP_NONE);
		facingLeft = false;
	}
	else if (velocityX < 0)
	{
		image->setFlip(SDL_FLIP_HORIZONTAL);
		extraAnimationSpace->setFlip(SDL_FLIP_HORIZONTAL);
		facingLeft = true;
	}

	//animations
	if (shooting)
	{
		image->setFrameRow(2);
		if (shootingFrameSpeed + shootingTimer < SDL_GetTicks())
		{
			image->setFrame(image->getFrame() + 1);
			shootingTimer = SDL_GetTicks();
			if (image->getFrame() >= 5)
			{
				shooting = false;
				shot = true;
			}
		}

	}

	if (!shooting && breaking)
	{
		image->setFrameRow(3);
		if (miningFrameSpeed + miningTimer < SDL_GetTicks())
		{
			image->setFrame(image->getFrame() + 1);
			if (image->getFrame() > 8)
			image->setFrame(0);

			extraAnimationSpace->setCrop(0, 88, 39, 38);
			extraAnimationSpace->setW(72);
			extraAnimationSpace->setH(60);
			extraAnimationSpace->setFrame(image->getFrame());

			miningTimer = SDL_GetTicks();
		}
	}
	else if (!shooting && landed)
	{
		image->setFrameRow(0);
		runningFrameSpeed = 40 * (10 / abs(velocityX));
		if (runningFrameSpeed + runningTimer < SDL_GetTicks())
		{
			
			image->setFrame(image->getFrame() + 1);
			runningTimer = SDL_GetTicks();
		}
		if (image->getFrame() > 7)
			image->setFrame(0);
	}
	else if (!shooting && !landed && (touchingLeft | touchingRight))
	{
		image->setFrameRow(1);
		image->setFrame(0);
	}
	else if (!shooting && !landed && !(touchingLeft | touchingRight))
	{
		image->setFrameRow(1);
		image->setFrame(1);
	}

	//drawing
	image->drawObject(playerTexture);
	if (breaking)
		breakingImage->drawObject(NULL);
	if (breaking)
	{
		extraAnimationSpace->setX(image->getX() + image->getW() / 2 - extraAnimationSpace->getW() / 2);
		extraAnimationSpace->setY(image->getY() + image->getH() / 2 - extraAnimationSpace->getH() / 2);
		extraAnimationSpace->drawObject(playerTexture);
	}

	//show pickUps to player
	if (pickUpText->getAlpha() > 0)
		pickUpText->writeObject("fonts/tinyreg.ttf", 20, pickUpString, image->getX() - 50, (image->getY() - 20) - (40 - 40 * ((float)pickUpText->getAlpha() / 255)), 1000, NULL, NULL);
	if (pickUpText->getAlpha() > 0)
		pickUpText->setAlpha(pickUpText->getAlpha() - 5);
	if (pickUpText->getAlpha() < 0)
		pickUpText->setAlpha(0);
}

void CPlayer::drawShot()
{
	shotImage->drawObject(NULL);
}

void CPlayer::displayStats()
{
	std::string statsString = " ";

	////////////////////////////
	/////////HEALTH/////////////
	////////////////////////////

	//show dealt damage to player
	if (dealtText->getAlpha() > 0)
		dealtText->writeObject("fonts/tinyreg.ttf", 20, dealtString, image->getX(), (image->getY() - 20) - (40 - 40*((float)dealtText->getAlpha()/255)), 100, NULL, NULL);
	if (dealtText->getAlpha() > 0)
		dealtText->setAlpha(dealtText->getAlpha() - 5);
	if (dealtText->getAlpha() < 0)
		dealtText->setAlpha(0);

	//actual health bar
	healthBar->setH(74 * (health / maxHealth));
	healthBar->setY(30 + 74 - 74 * (health / maxHealth));
	healthBar->setCrop(0, 37 - 37 * (health / maxHealth), 38, 37 * (health / maxHealth));

	emptyHealthBar->drawStatic(NULL);
	healthBar->drawStatic(NULL);

	////////////////////////////
	/////////STATS//////////////
	////////////////////////////

	//pickaxe
	pickaxeStatsPicture->drawStatic(statsTexture);
	statsString = "Lv. " + std::to_string(pickaxeLevel);
	statsText[0]->write("fonts/tinyFill.ttf", 10, statsString, 155, 100, 1000, NULL, NULL);

	//health
	healthStatsPicutre->drawStatic(statsTexture);
	statsString = "Lv. " + std::to_string(healthLevel);
	statsText[0]->write("fonts/tinyFill.ttf", 10, statsString, 305, 100, 1000, NULL, NULL);

	//money
	moneyStatsPicture->drawStatic(statsTexture);
	statsString = "Lv. " + std::to_string(moneyLevel);
	statsText[0]->write("fonts/tinyFill.ttf", 10, statsString, 455, 100, 1000, NULL, NULL);

	////////////////////////////
	//////////MONEY/////////////
	////////////////////////////

	statsString = "$" + std::to_string(money);
	moneyText->write("fonts/tinyFill.ttf", 50, statsString, 15, sdl_Setup->getScreenHeight() - 65, NULL, NULL, NULL);

}

void CPlayer::displayInventory()
{
	std::string oreAmount = " ";

	//iron
	oreAmount = "x" + std::to_string(ironCount);
	inventoryText->write("fonts/tinyreg.ttf", 10, oreAmount, 80, 200, 1000, NULL, NULL);
	oreImage[0]->drawStatic(world->getTileSet());

	//copper
	oreAmount = "x" + std::to_string(copperCount);
	inventoryText->write("fonts/tinyreg.ttf", 10, oreAmount, 80, 250, 1000, NULL, NULL);
	oreImage[1]->drawStatic(world->getTileSet());
	
	//gold
	oreAmount = "x" + std::to_string(goldCount);
	inventoryText->write("fonts/tinyreg.ttf", 10, oreAmount, 80, 300, 1000, NULL, NULL);
	oreImage[2]->drawStatic(world->getTileSet());
}

void CPlayer::move()
{
	//x pos
	if (!playerLocked)
	{
		if (!shooting && !(breaking && landed))
		{
			if (getPressed(input, 0) && velocityX >= -5)
			{
				velocityX -= 0.3;
			}
			else if (getPressed(input, 1) && velocityX <= 5)
			{
				velocityX += 0.3;
			}
		}

		//y pos
		if (getPressed(input, 2) && jumpDurration < jumpMaxDurration)
		{
			if (landed && image->getX() / 40 >= 0 && image->getX() / 40 < world->getWidth() && image->getY() / 40 - 1 >= 0 && image->getY() / 40 - 1 < world->getHeight())
			{
				if (world->getBlock(image->getX() / 40, image->getY() / 40 - 1)->getPassable())
				{
					velocityY = -5;
					jumpDurration++;
					if (landed)
						jumpedLast = SDL_GetTicks();
				}
			}
			else if (landed && image->getX() / 40 + 1 >= 0 && image->getX() / 40 + 1 < world->getWidth() && image->getY() / 40 - 1 >= 0 && image->getY() / 40 - 1 < world->getHeight())
			{
				if (world->getBlock(image->getX() / 40 + 1, image->getY() / 40 - 1)->getPassable())
				{
					velocityY = -5;
					jumpDurration++;
					if (landed)
						jumpedLast = SDL_GetTicks();
				}
			}
			else
			{
				velocityY = -5;
				jumpDurration++;
				if (landed)
					jumpedLast = SDL_GetTicks();
			}
		}
		if (!getPressed(input, 2) && !landed)
		{
			jumpDurration = jumpMaxDurration + 1;
		}
		if (landed)
			jumpDurration = 0;

		if (!landed && getPressed(input, 2) && touchingRight && jumpDurration > jumpMaxDurration && jumpedLast + 200 < SDL_GetTicks())
		{
			velocityY = -5;
			velocityX = -6;
			jumpDurration = 0;
			jumpedLast = SDL_GetTicks();
		}
		else if (!landed && getPressed(input, 2) && touchingLeft && jumpDurration > jumpMaxDurration && jumpedLast + 200 < SDL_GetTicks())
		{
			velocityY = -5;
			velocityX = 6;
			jumpDurration = 0;
			jumpedLast = SDL_GetTicks();
		}
	}
	//gravity and friction
	if (((!getPressed(input, 0) && !getPressed(input, 1)) | shooting | breaking | playerLocked) && landed)
	{
		if (velocityX > 0)
			velocityX -= 0.3;
		else if (velocityX < 0)
			velocityX += 0.3;
		if (abs(velocityX) < 0.3)
			velocityX = 0;
	}
	velocityY += gravity;
	if (velocityY > 40)
		velocityY = 40;

	//x pos wall collisions
	image->setX(image->getX() + velocityX);
	
	for (int y = image->getY() / 40; y < (image->getY() / 40) + 2; y++)
	{
		for (int x = image->getX() / 40; x < (image->getX() / 40) + 2; x++)
		{
			if (x >= 0 && x < world->getWidth() && y >= 0 && y < world->getHeight())
			{
				if (!(image->getX() + image->getW() <= world->getBlock(x, y)->getRect().x || world->getBlock(x, y)->getRect().x + world->getBlock(x, y)->getRect().w <= image->getX() || image->getY() + image->getH() <= world->getBlock(x, y)->getRect().y || world->getBlock(x, y)->getRect().y + world->getBlock(x, y)->getRect().h <= image->getY()))
				{
					//solid block mechanics
					if (!world->getBlock(x, y)->getPassable())
					{
						if (velocityX > 0) { image->setX(world->getBlock(x, y)->getRect().x - image->getW()); }
						if (velocityX < 0) { image->setX(world->getBlock(x, y)->getRect().x + world->getBlock(x, y)->getRect().w); }
						velocityX = 0;
					}
					// waterfall mechanics
					if (world->getBlock(x, y)->getType() == 7)
					{
						if (velocityX > 3 && !landed)
							velocityX--;
						else if (velocityX < -3 && !landed)
							velocityX++;
						if (velocityY > 3)
							velocityY--;
						else if (velocityY < -3)
							velocityY++;
					}
				}
			}
		}
	}

	touchingLeft = false;
	touchingRight = false;
	if (image->getX() / 40 - 1 >= 0 && image->getX() / 40 - 1 < world->getWidth() && image->getY() / 40 >= 0 && image->getY() / 40 < world->getHeight())
	{
		if (image->getX() == world->getBlock(image->getX() / 40 - 1, image->getY() / 40)->getRect().x + world->getBlock(image->getX() / 40 - 1, image->getY() / 40)->getRect().w && !world->getBlock(image->getX() / 40 - 1, image->getY() / 40)->getPassable())
			touchingLeft = true;
	}
	if (image->getX() / 40 + 1 >= 0 && image->getX() / 40 + 1 < world->getWidth() && image->getY() / 40 >= 0 && image->getY() / 40 < world->getHeight())
	{
		if (image->getX() + image->getW() == world->getBlock(image->getX() / 40 + 1, image->getY() / 40)->getRect().x && !world->getBlock(image->getX() / 40 + 1, image->getY() / 40)->getPassable())
			touchingRight = true;
	}

	//y pos ground and celling collisions
	image->setY(image->getY() + velocityY);

	for (int y = image->getY() / 40; y < (image->getY() / 40) + 2; y++)
	{
		for (int x = image->getX() / 40; x < (image->getX() / 40) + 2; x++)
		{
			if (x >= 0 && x < world->getWidth() && y >=0 && y < world->getHeight())
			{
				if (!world->getBlock(x, y)->getPassable() && !(image->getX() + image->getW() <= world->getBlock(x, y)->getRect().x || world->getBlock(x, y)->getRect().x + world->getBlock(x, y)->getRect().w <= image->getX() || image->getY() + image->getH() <= world->getBlock(x, y)->getRect().y || world->getBlock(x, y)->getRect().y + world->getBlock(x, y)->getRect().h <= image->getY()))
				{
					if (velocityY > 0)
					{
						image->setY(world->getBlock(x, y)->getRect().y - image->getH());
						if (velocityY > 10)
							takeDamage(velocityY - 10);
						velocityY = 0;
					}
					if (velocityY < 0)
					{
						image->setY(world->getBlock(x, y)->getRect().y + world->getBlock(x, y)->getRect().h);
						velocityY = 0;
						jumpDurration = jumpMaxDurration;
					}
				}
			}
		}
	}
	
	bool wasLanded = landed;
	landed = false; //makes sure to check everytime
	if ((image->getY() / 40) + 1 < world->getHeight() && (image->getY() / 40) + 1 >= 0 && image->getX() / 40 < world->getWidth() && image->getX() / 40 >= 0)
	{
		if (image->getY() + image->getH() == world->getBlock(image->getX() / 40, (image->getY() / 40) + 1)->getRect().y && !world->getBlock(image->getX() / 40, (image->getY() / 40) + 1)->getPassable())
			landed = true;
	}
	if ((image->getY() / 40) + 1 < world->getHeight() && (image->getY() / 40) + 1 >= 0 && image->getX() / 40 + 1 < world->getWidth() && image->getX() / 40 + 1 >= 0 && wasLanded)
	{
		if (image->getY() + image->getH() == world->getBlock(image->getX() / 40 + 1, (image->getY() / 40) + 1)->getRect().y && !world->getBlock(image->getX() / 40 + 1, (image->getY() / 40) + 1)->getPassable())
			landed = true;
	}

	//update players position in world
	world->setPlayerPosition(image->getX(), image->getY());
}

void CPlayer::dig()
{
	int x = image->getX() / 40;
	int y = image->getY() / 40;

	breaking = false;

	if (!shooting && !playerLocked)
	{
		if (y < world->getHeight() && y >= 0 && x - 1 < world->getWidth() && x - 1 >= 0)
		{
			if (getPressed(input, 0) && image->getX() == world->getBlock(x - 1, y)->getRect().x + world->getBlock(x - 1, y)->getRect().w && !world->getBlock(x - 1, y)->getPassable())
			{
				damageDone++;
				breakingX = x - 1;
				breakingY = y;
				if (damageDone > world->getBlock(x - 1, y)->getStrength())
				{
					world->destoryBlock(x - 1, y);
					damageDone = 0;
				}
				breaking = true;
			}
		}

		if (y < world->getHeight() && y >= 0 && x + 1 < world->getWidth() && x + 1 >= 0)
		{
			if (getPressed(input, 1) && !breaking && image->getX() + image->getW() == world->getBlock(x + 1, y)->getRect().x && !world->getBlock(x + 1, y)->getPassable())
			{
				damageDone++;
				breakingX = x + 1;
				breakingY = y;
				if (damageDone > world->getBlock(x + 1, y)->getStrength())
				{
					world->destoryBlock(x + 1, y);
					damageDone = 0;
				}
				breaking = true;
			}
		}

		if (y - 1 < world->getHeight() && y - 1 >= 0 && x < world->getWidth() && x >= 0)
		{
			if (getPressed(input, 2) && !breaking && !world->getBlock(x, y - 1)->getPassable())
			{
				damageDone++;
				breakingX = x;
				breakingY = y - 1;
				if (damageDone > world->getBlock(x, y - 1)->getStrength())
				{
					world->destoryBlock(x, y - 1);
					damageDone = 0;
				}
				breaking = true;
			}
		}

		if (y + 1 < world->getHeight() && y + 1 >= 0 && x < world->getWidth() && x >= 0)
		{
			if (getPressed(input, 3) && !breaking && image->getY() + image->getH() == world->getBlock(x, y + 1)->getRect().y && !world->getBlock(x, y + 1)->getPassable())
			{
				damageDone++;
				breakingX = x;
				breakingY = y + 1;
				if (damageDone > world->getBlock(x, y + 1)->getStrength())
				{
					world->destoryBlock(x, y + 1);
					//world->getBlock(x, y + 1)->setType(0);
					damageDone = 0;
				}
				breaking = true;
			}
		}
	}
	if (!(getPressed(input, 0) | getPressed(input, 1) | getPressed(input, 2) | getPressed(input, 3)) | breakingX != lastBreakingX | breakingY != lastBreakingY | shooting)
		damageDone = 0;

	lastBreakingX = breakingX;
	lastBreakingY = breakingY;

	breakingImage->setX(breakingX * 40);
	breakingImage->setY(breakingY * 40);
	breakingImage->setFrame(10 * ((float)damageDone / (float)world->getBlock(breakingX, breakingY)->getStrength()));
}

void CPlayer::shootGun()
{
	if (getPressed(input, 4) && !shooting && !playerLocked)
	{
		shooting = true;
		image->setFrame(0);
	}
	shotImage->setY(image->getY() + 12);
	if (!facingLeft)
		shotImage->setX(image->getX() + image->getW());
	if (facingLeft)
		shotImage->setX(image->getX() - shotImage->getW());
	if (shotImage->getAlpha() > 0)
		shotImage->setAlpha(shotImage->getAlpha() - 20);
	if (shotImage->getAlpha() < 0)
		shotImage->setAlpha(0);

	if (shot)
	{
		shotImage->setAlpha(255);
		playerSounds->playSound(2);
		shot = false;
	}
}

void CPlayer::pickUpDrops()
{
	for (int i = 0; i < world->getDropsMax(); i++)
	{
		if (world->getDrop(i)->getActive() && !(image->getRect().x + image->getRect().w < world->getDrop(i)->getImage()->getRect().x || world->getDrop(i)->getImage()->getRect().x + world->getDrop(i)->getImage()->getRect().w < image->getRect().x || image->getRect().y + image->getRect().h < world->getDrop(i)->getImage()->getRect().y || world->getDrop(i)->getImage()->getRect().y + world->getDrop(i)->getImage()->getRect().h < image->getRect().y))
		{
			world->getDrop(i)->setActive(false);
			
			int value = 0;

			if (world->getDrop(i)->getType() == 0)
			{
				ironCount++;
				money += 2;
				value = 2;
			}
			if (world->getDrop(i)->getType() == 1)
			{
				copperCount++;
				money += 5;
				value = 5;
			}
			if (world->getDrop(i)->getType() == 2)
			{
				goldCount++;
				money += 10;
				value = 10;
			}

			pickUpString = "$" + std::to_string(value);
			pickUpText->setAlpha(255);
			playerSounds->playSound(1);
		}
	}
}

void CPlayer::buyUpgrades()
{
	if (getShopPlayerIsInX() != -1)
	{
		if (world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentPrice() != 0 && world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentPrice() <= money && getPressed(input, 7) && world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getActive())
		{
			world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->buyItem();
			money -= world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentPrice();

			if (world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentItem() == 0)
			{
				pickaxeLevel++;
			}
			if (world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentItem() == 1)
			{
				healthLevel++;
			}
			if (world->getShop(getShopPlayerIsInX(), getShopPlayerIsInY())->getCurrentItem() == 2)
			{
				moneyLevel++;
			}
		}
	}
}

void CPlayer::takeDamage(int damageAmount)
{
	health -= damageAmount;
	if (damageAmount > 0)
		dealtText->setColor(193, 0, 0);
	else if (damageAmount < 0)
		dealtText->setColor(59, 236, 65);

	if (damageAmount != 0)
	{
		dealtText->setAlpha(255);
		dealtString = std::to_string(abs(damageAmount));
	}
}

void CPlayer::lockPlayer(bool locked)
{
	playerLocked = locked;
}

void CPlayer::setPlayerXVelocity(float newVelocity)
{
	velocityX = newVelocity;
}

float CPlayer::getPlayerYVelocity()
{
	return velocityY;
}

Csprites* CPlayer::getImage()
{
	return image;
}