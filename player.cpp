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

void Player::setYellowColor() { this->setTexture(&yellowTexture); }

void Player::setBlueColor() { this->setTexture(&blueTexture); }

void Player::setRedColor() { this->setTexture(&redTexture); }

double Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(double speed)
{
	this->speed = speed;
}