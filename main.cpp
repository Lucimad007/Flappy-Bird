#include <SFML\Graphics.hpp>
#include "player.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
Player player(WIDTH/3, HEIGHT/2, 0.05f);

void update();
void render();
void movePlayer();

int main() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	sf::Event windowEvent;

	bool isReleased = true;
	while (window->isOpen())
	{
		window->clear();

		while (window->pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				window->close();
			else if (windowEvent.type == sf::Event::KeyPressed)
			{
				if (windowEvent.key.code == sf::Keyboard::Space)
					if (isReleased) 
					{
						player.flap();
						isReleased = false;
					}
			}
			else if (windowEvent.type == sf::Event::KeyReleased)
			{
				isReleased = true;
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
	movePlayer();
}

void render()
{
	window->draw(player);
}

void movePlayer()
{
	player.move(0, -player.getSpeed());
	player.setSpeed(player.getSpeed() - 0.001f * player.getGravity());
}