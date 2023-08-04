#include <SFML\Graphics.hpp>
#include "player.h"
#include "background-manager.h"

const int WIDTH = 800;
const int HEIGHT = 500;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
Player player(WIDTH/3, HEIGHT/2, 0.05f);
BackgroundManager* backgroundManager;

void update();
void render();
void movePlayer();

int main() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	backgroundManager = new BackgroundManager(window);
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
	backgroundManager->drawNight();
	backgroundManager->drawGround();
	window->draw(player);
}

void movePlayer()
{
	player.move(0, -player.getSpeed());
	backgroundManager->setVerticalOffset(backgroundManager->getVerticalOffset() - player.getSpeed()/2);
	player.setSpeed(player.getSpeed() - 0.001f * player.getGravity());
}