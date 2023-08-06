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
	void drawScore();

	double getHorizontalOffset();
	void setHorizontalOffset(double offset);

	void generatePrimaryPipes();
	void movePipes(double offset);
	void updatePipes();
	void moveGround(double offset);
	bool intersectsGround(double height, double length);
	void resetPositionOfNumbers();
	void updateScore();
	int getScore();
	bool isDay();

	const std::list<Pipe>& getPipes();

private:
	sf::RenderWindow* window = nullptr;
	sf::Sprite daySprite, nightSprite, groundSprite;
	sf::Texture dayTexture, nightTexture, groundTexture;
	sf::Sprite numberSprite[10];	//0 - 9
	sf::Texture numberTexture[10];	//0 - 9
	double horizontalOffset = 0;
	double ground_y = 50;		//y relative to bottom
	const double gapBetweenPipes = 100;
	double pipesHeightRelativeToGround = 50;
	double pipesLastHeight = 0;
	std::list<Pipe> pipes;
	int score = 0;
	const double scoreGapRelativeToWindow = 30;
};

