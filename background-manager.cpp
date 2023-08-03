#include "background-manager.h"

BackgroundManager::BackgroundManager(sf::RenderWindow* inputWindow)
{
	window = inputWindow;
	dayTexture.loadFromFile("assets\\sprites\\background-day.png");
	nightTexture.loadFromFile("assets\\sprites\\background-night.png");
	daySprite.setTexture(dayTexture);
	nightSprite.setTexture(nightTexture);
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