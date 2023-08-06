#include <SFML\Graphics.hpp>
#include "player.h"
#include "background-manager.h"
#include <iostream>

bool RUNNING = true;
const int WIDTH = 800;
const int HEIGHT = 500;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
Player player(WIDTH/3, HEIGHT/2, 0.05f);
BackgroundManager* backgroundManager;

void update();
void render();
void movePlayer();
void detectCollisions();

int main() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	backgroundManager = new BackgroundManager(window);
	backgroundManager->generatePrimaryPipes();
	sf::Event windowEvent;

	bool isReleased = true;
	while (RUNNING)
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
	backgroundManager->updatePipes();
	backgroundManager->movePipes(player.getSpeed());
	detectCollisions();
	movePlayer();
	backgroundManager->updateScore();
}

void render()
{
	backgroundManager->drawNight();
	backgroundManager->drawGround();
	for (auto it = backgroundManager->getPipes().begin(); it != backgroundManager->getPipes().end(); ++it)
	{
		window->draw(*it);
	}
	backgroundManager->drawScore();
	window->draw(player);
}

void movePlayer()
{
	player.move(0, -player.getSpeed());
	backgroundManager->moveGround(-player.getSpeed());
	player.setSpeed(player.getSpeed() - 0.001f * player.getGravity());
}

void detectCollisions()
{
	//ground
	if (backgroundManager->intersectsGround(player.getPosition().y, player.getSize().y))
	{
		RUNNING = false;
		return;
	}
	//pipes
	for (auto it = backgroundManager->getPipes().begin(); it != backgroundManager->getPipes().end(); it++)
	{
		if (it->intersects(player))
		{
			RUNNING = false;
			return;
		}
	}
}