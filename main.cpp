#include <SFML\Graphics.hpp>
#include "player.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
Player player;

void update();
void render();

int main() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	sf::Event windowEvent;

	while (window->isOpen())
	{
		window->clear();

		while (window->pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::Closed : 
				window->close();
				break;
			default:
				break;
			}
		}

		update();	//logic
		render();	//visual

		window->display();
	}

	return 0;
}

void update() 
{

}

void render()
{
	window->draw(player.getSprite());
}

