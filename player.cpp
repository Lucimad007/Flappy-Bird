#include "player.h"
#include "background-manager.h"

extern BackgroundManager* backgroundManager;

Player::Player(int x, int y, int speed)
{
	this->setSize(sf::Vector2f(width, height));
	this->setPosition(x, y);
	this->speed = speed;
	this->texture.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	this->setTexture(&texture);
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

double Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(double speed)
{
	this->speed = speed;
}

sf::Sprite Player::getSprite() {
	return sprite;
}