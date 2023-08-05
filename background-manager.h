#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include "pipe.h"

class BackgroundManager : public sf::RectangleShape
{
public:
	BackgroundManager(sf::RenderWindow* inputWindow);
	void drawDay();
	void drawNight();
	void drawGround();

	double getHorizontalOffset();
	void setHorizontalOffset(double offset);

	void generatePrimaryPipes();
	void movePipes(double offset);
	void updatePipes();
	void moveGround(double offset);
	bool intersectsGround(double height, double length);

	const std::list<Pipe>& getPipes();

private:
	sf::RenderWindow* window = nullptr;
	sf::Sprite daySprite, nightSprite, groundSprite;
	sf::Texture dayTexture, nightTexture, groundTexture;
	double horizontalOffset = 0;
	double ground_y = 50;		//y relative to bottom
	double gapBetweenPipes = 100;
	double pipesHeightRelativeToGround = 50;
	double pipesLastHeight = 0;
	std::list<Pipe> pipes{};
};

