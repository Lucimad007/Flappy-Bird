#include "button.h"

extern sf::RenderWindow* window;

Button::Button(sf::Vector2f vec) :
	sf::RectangleShape(vec)
{

}
void Button::setButtonHandler(void (*functionPtr)())
{
	this->functionPtr = functionPtr;
}

void Button::isClicked()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		double x_mouse, y_mouse, min_x, min_y, max_x, max_y;
		x_mouse = sf::Mouse::getPosition(*window).x;
		y_mouse = sf::Mouse::getPosition(*window).y;
		min_x = this->getPosition().x;
		max_x = min_x + this->getSize().x;
		min_y = this->getPosition().y;
		max_y = min_y + this->getSize().y;
			
		if (x_mouse > min_x && x_mouse < max_x)
			if (y_mouse > min_y && y_mouse < max_y)
				functionPtr();
	}
}