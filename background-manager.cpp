#include "background-manager.h"
#include <iostream>

BackgroundManager::BackgroundManager(sf::RenderWindow* inputWindow)
{
	window = inputWindow;
	dayTexture.loadFromFile("assets\\sprites\\background-day.png");
	nightTexture.loadFromFile("assets\\sprites\\background-night.png");
	groundTexture.loadFromFile("assets\\sprites\\base.png");
	daySprite.setTexture(dayTexture);
	nightSprite.setTexture(nightTexture);
	groundSprite.setTexture(groundTexture);
}

void BackgroundManager::drawDay()
{
	int size = dayTexture.getSize().x;
	for (int i = 0; i < window->getSize().x; i += size)
	{
		daySprite.setPosition(sf::Vector2f(i, 0));
		window->draw(daySprite);
	}
	daySprite.setPosition(sf::Vector2f(0, 0));
}

void BackgroundManager::drawNight()
{
	int size = nightTexture.getSize().x;
	for (int i = 0; i < window->getSize().x; i += size)
	{
		nightSprite.setPosition(sf::Vector2f(i, 0));
		window->draw(nightSprite);
	}
	nightSprite.setPosition(sf::Vector2f(0, 0));
}

void BackgroundManager::drawGround()
{
	horizontalOffset -= 0.25f;
	int size = groundTexture.getSize().x;
	if (horizontalOffset <= -size)		//ground moves backward so we think we are moving forward
		horizontalOffset = 0;

	//
	for (double j = 0; j <= verticalOffset; j += groundTexture.getSize().y / 2)
	{
		for (double i = horizontalOffset - size; i < window->getSize().x; i += size)
		{
			groundSprite.setPosition(sf::Vector2f(i, window->getSize().y - groundTexture.getSize().y - j));
			window->draw(groundSprite);
		}
	}

	//outer layer of ground
	for (double i = horizontalOffset - size; i < window->getSize().x; i += size)
	{
		groundSprite.setPosition(sf::Vector2f(i, window->getSize().y - groundTexture.getSize().y - verticalOffset));
		window->draw(groundSprite);
	}

	window->draw(groundSprite);

	groundSprite.setPosition(sf::Vector2f(0, window->getSize().y - groundTexture.getSize().y - verticalOffset));
}

double BackgroundManager::getVerticalOffset() { return verticalOffset; }
void BackgroundManager::setVerticalOffset(double offset) { this->verticalOffset = offset; }

double BackgroundManager::getHorizontalOffset() { return horizontalOffset; }
void BackgroundManager::setHorizontalOffset(double offset) { this->horizontalOffset = offset; }