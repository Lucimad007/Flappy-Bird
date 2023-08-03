#pragma once
#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	Player(int x, int y);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);

	sf::Sprite getSprite();

private:
	int x, y;
	sf::Sprite sprite;
	sf::Texture texture;
};

