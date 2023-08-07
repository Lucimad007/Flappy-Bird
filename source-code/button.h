#pragma once
#include <SFML\Graphics.hpp>

class Button : public sf::RectangleShape
{
public:
	Button() = default;
	Button(sf::Vector2f vec);
	void setButtonHandler(void (*functionPtr)());
	void isClicked();
private:
	void (*functionPtr)();
};

