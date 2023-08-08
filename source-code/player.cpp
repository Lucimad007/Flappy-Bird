#include "player.h"
#include "background-manager.h"
#include "audio-manager.h"

extern BackgroundManager* backgroundManager;
extern AudioManager audioManager;

Player::Player(double x, double y, double speed)
{
	this->setSize(sf::Vector2f(width, height));
	this->setPosition(x, y);
	this->speed = speed;
	this->redTextureUp.loadFromFile("assets\\sprites\\redbird-upflap.png");
	this->blueTextureUp.loadFromFile("assets\\sprites\\bluebird-upflap.png");
	this->yellowTextureUp.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	this->redTextureDown.loadFromFile("assets\\sprites\\redbird-downflap.png");
	this->blueTextureDown.loadFromFile("assets\\sprites\\bluebird-downflap.png");
	this->yellowTextureDown.loadFromFile("assets\\sprites\\yellowbird-downflap.png");
	this->redTextureMid.loadFromFile("assets\\sprites\\redbird-midflap.png");
	this->blueTextureMid.loadFromFile("assets\\sprites\\bluebird-midflap.png");
	this->yellowTextureMid.loadFromFile("assets\\sprites\\yellowbird-midflap.png");
	this->setTexture(&yellowTextureUp);
	this->setSize(sf::Vector2f(yellowTextureUp.getSize().x, yellowTextureUp.getSize().y));    //all bird textures have the same size
}

double Player::getGravity() 
{
	return gravity;
}

void Player::flap()
{
	audioManager.playSwoosh();
	if (speed <= 0)
		speed = flapSpeed;
	else
		speed += flapSpeed;
}

void Player::setYellowColor()
{
	if (birdState == UP_WING)
		this->setTexture(&yellowTextureUp);
	else if (birdState == DOWN_WING)
		this->setTexture(&yellowTextureDown);
	else if (birdState == MID_WING)
		this->setTexture(&yellowTextureMid);
	this->birdColor = YELLOW_BIRD;
}

void Player::setBlueColor() 
{ 
	if (birdState == UP_WING)
		this->setTexture(&blueTextureUp);
	else if (birdState == DOWN_WING)
		this->setTexture(&blueTextureDown);
	else if (birdState == MID_WING)
		this->setTexture(&blueTextureMid);
	this->birdColor = BLUE_BIRD;
}

void Player::setRedColor() 
{ 
	if (birdState == UP_WING)
		this->setTexture(&redTextureUp);
	else if (birdState == DOWN_WING)
		this->setTexture(&redTextureDown);
	else if (birdState == MID_WING)
		this->setTexture(&redTextureMid);
	this->birdColor = RED_BIRD;
}

void Player::updateColor(int score)
{
	if (birdColor == RED_BIRD)
	{
		return;
	}
	else if (birdColor != RED_BIRD && score >= SPECIAL_SCORE)
	{
		setRedColor();
		return;
	}

	if (backgroundManager->isDay())
	{
		setYellowColor();
	}
	else {
		setBlueColor();
	}
}

double Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(double speed)
{
	this->speed = speed;
}

void Player::reset()
{
	this->setPosition(X_INIT, Y_INIT);
	speed = SPEED_INIT;
	setYellowColor();
}

void Player::updateState()
{
	if (birdColor == RED_BIRD) {
		if (birdState == UP_WING)
		{
			this->setTexture(&redTextureMid);
			birdState = MID_WING;
		}
		else if (birdState == MID_WING)
		{
			this->setTexture(&redTextureDown);
			birdState = DOWN_WING;
		}
		else if (birdState == DOWN_WING)
		{
			this->setTexture(&redTextureUp);
			birdState = UP_WING;
		}
	}
	else if (birdColor == YELLOW_BIRD)
	{
		if (birdState == UP_WING)
		{
			this->setTexture(&yellowTextureMid);
			birdState = MID_WING;
		}
		else if (birdState == MID_WING)
		{
			this->setTexture(&yellowTextureDown);
			birdState = DOWN_WING;
		}
		else if (birdState == DOWN_WING)
		{
			this->setTexture(&yellowTextureUp);
			birdState = UP_WING;
		}
	}
	else if (birdColor == BLUE_BIRD)
	{
		if (birdState == UP_WING)
		{
			this->setTexture(&blueTextureMid);
			birdState = MID_WING;
		}
		else if (birdState == MID_WING)
		{
			this->setTexture(&blueTextureDown);
			birdState = DOWN_WING;
		}
		else if (birdState == DOWN_WING)
		{
			this->setTexture(&blueTextureUp);
			birdState = UP_WING;
		}
	}
}