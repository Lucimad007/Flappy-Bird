#pragma once
#include <SFML\Graphics.hpp>

class BackgroundManager : public sf::RectangleShape
{
public:
	BackgroundManager(sf::RenderWindow* inputWindow);
	void drawDay();
	void drawNight();
private:
	sf::RenderWindow* window = nullptr;
	sf::Sprite daySprite, nightSprite;
	sf::Texture dayTexture, nightTexture;
};

