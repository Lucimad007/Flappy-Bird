#include <SFML\Graphics.hpp>
#include "player.h"
#include "background-manager.h"
#include "button.h"
#include <iostream>

bool RUNNING = true;
const int WIDTH = 800;
const int HEIGHT = 500;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
const int X_INIT = WIDTH / 3, Y_INIT = HEIGHT / 2;
const double SPEED_INIT = 0.05f;
Player player(X_INIT, Y_INIT, SPEED_INIT);
BackgroundManager* backgroundManager;
Button* restartButton;

void loadIcon();
void update();
void render();
void movePlayer();
void detectCollisions();
void checkButtonEvents();
void on_restart_button();

int main() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	loadIcon();
	backgroundManager = new BackgroundManager(window);
	sf::Event windowEvent;
	
	sf::Texture* gameOverTexture = new sf::Texture();
	gameOverTexture->loadFromFile("assets\\sprites\\gameover.png");	
	restartButton = new Button(sf::Vector2f(gameOverTexture->getSize().x, gameOverTexture->getSize().y));
	restartButton->setTexture(gameOverTexture);
	restartButton->setPosition(200, 200);
	restartButton->setButtonHandler(on_restart_button);

	bool isReleased = true;
	while (window->isOpen())
	{
		while (window->pollEvent(windowEvent))
		{
			checkButtonEvents();

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

		if (!RUNNING)	//for stopping game loop
		{
			continue;
		}

		window->clear();
		update();	//logic
		render();	//visual

		window->display();

		if (!RUNNING)
		{
			window->draw(*restartButton);
			window->display();
		}
	}

	return 0;
}

void loadIcon()
{
	sf::Image icon;
	icon.loadFromFile("assets\\favicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
	//background
	if(backgroundManager->getScore()/10 % 2)
		backgroundManager->drawDay();
	else 
		backgroundManager->drawNight();

	//pipes
	for (auto it = backgroundManager->getPipes().begin(); it != backgroundManager->getPipes().end(); ++it)
	{
		window->draw(*it);
	}
	//ground
	backgroundManager->drawGround();
	//score
	backgroundManager->drawScore();
	//player
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

void checkButtonEvents()
{
	restartButton->isClicked();
}

void on_restart_button()
{
	backgroundManager = new BackgroundManager(window);
	player.setPosition(X_INIT, Y_INIT);
	player.setSpeed(SPEED_INIT);
	RUNNING = true;
}