#include "player.h"
#include "background-manager.h"

extern BackgroundManager* backgroundManager;

Player::Player(int x, int y, int speed)
{
	this->setSize(sf::Vector2f(width, height));
	this->setPosition(x, y);
	this->speed = speed;
	this->redTexture.loadFromFile("assets\\sprites\\redbird-upflap.png");
	this->blueTexture.loadFromFile("assets\\sprites\\bluebird-upflap.png");
	this->yellowTexture.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	this->setTexture(&yellowTexture);
}

double Player::getGravity() 
{
	return gravity;
}

void Player::flap()
{
	if (speed <= 0)
		speed = flapSpeed;
	else
		speed += flapSpeed;
	move(0, speed);
	backgroundManager->moveGround(-speed);
}

void Player::setYellowColor()
{
	this->setTexture(&yellowTexture);
	this->birdColor = YELLOW_BIRD;
}

void Player::setBlueColor() 
{ 
	this->setTexture(&blueTexture); 
	this->birdColor = BLUE_BIRD;
}

void Player::setRedColor() 
{ 
	this->setTexture(&redTexture); 
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