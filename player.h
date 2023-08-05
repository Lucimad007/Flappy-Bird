#pragma once
#include <SFML\Graphics.hpp>

class Player : public sf::RectangleShape
{
public:
	Player(int x = 0, int y = 0, int speed = 0);

	double getSpeed();
	void setSpeed(double speed);

	sf::Sprite getSprite();
	double getGravity();

	void flap();

private:
	const int width = 32;
	const int height = 32;
	double speed;		//vertical speed
	const double gravity = 2;
	const double flapSpeed = 0.25;
	int mass = 1;
	sf::Sprite sprite;
	sf::Texture texture;
};

