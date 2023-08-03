#pragma once
#include <SFML\Graphics.hpp>

class BackgroundManager : public sf::RectangleShape
{
public:
	BackgroundManager(sf::RenderWindow* inputWindow);
	void drawDay();
	void drawNight();
	void drawGround();
private:
	sf::RenderWindow* window = nullptr;
	sf::Sprite daySprite, nightSprite, groundSprite;
	sf::Texture dayTexture, nightTexture, groundTexture;
	double offset = 0;
};

