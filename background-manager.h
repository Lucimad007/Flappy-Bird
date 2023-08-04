#pragma once
#include <SFML\Graphics.hpp>

class BackgroundManager : public sf::RectangleShape
{
public:
	BackgroundManager(sf::RenderWindow* inputWindow);
	void drawDay();
	void drawNight();
	void drawGround();

	double getVerticalOffset();
	void setVerticalOffset(double offset);

	double getHorizontalOffset();
	void setHorizontalOffset(double offset);

private:
	sf::RenderWindow* window = nullptr;
	sf::Sprite daySprite, nightSprite, groundSprite;
	sf::Texture dayTexture, nightTexture, groundTexture;
	double horizontalOffset = 0;
	double verticalOffset = 0;
};

