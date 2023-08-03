#include "player.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->texture.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	this->sprite.setTexture(texture);
}

Player::Player(int x, int y)
{
	this->x = x;
	this->y = y;
	this->texture.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	this->sprite.setTexture(texture);
}

int Player::getX() {
	return x;
}
void Player::setX(int x) {
	this->x = x;
}

int Player::getY() {
	return y;
}
void Player::setY(int y) {
	this->y = y;
}

sf::Sprite Player::getSprite() {
	return sprite;
}