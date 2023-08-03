#include "background-manager.h"

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
	offset -= 0.25f;
	int size = groundTexture.getSize().x;
	if (offset <= -size)		//ground moves backward so we think we are moving forward
		offset = 0;
	for (double i = offset - size; i < window->getSize().x; i += size)
	{
		groundSprite.setPosition(sf::Vector2f(i, window->getSize().y - groundTexture.getSize().y));
		window->draw(groundSprite);
	}
	groundSprite.setPosition(sf::Vector2f(0, window->getSize().y - groundTexture.getSize().y));
}