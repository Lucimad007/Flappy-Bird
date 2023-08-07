#include <SFML\Graphics.hpp>
#include "player.h"
#include "background-manager.h"
#include "button.h"
#include "audio-manager.h"
#include <iostream>
#include <string>

AudioManager audioManager;
bool RUNNING = true;
const int WIDTH = 800;
const int HEIGHT = 500;
const int FPS_CAP = 60;		//frames per second
const int UPS_CAP = 60;		//updates per second
const double UPDATE_TIME = 1.0 / 60.0;
int Player::SPEED_INIT = 0.5f;
double Player::Y_INIT = HEIGHT / 2;
double Player::X_INIT = WIDTH / 3;
const std::string TITLE = "Flappy Bird";
sf::RenderWindow* window;
Player player(Player::X_INIT, Player::Y_INIT, Player::SPEED_INIT);
BackgroundManager* backgroundManager;
Button* restartButton;
double delta_time = 0;
sf::Clock game_clock;

void loadIcon();
void update();
void render();
void movePlayer();
void detectCollisions();
void checkButtonEvents();
void on_restart_button();

int main() {
	srand(NULL);	//NULL is defined as 0
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(FPS_CAP);
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

	game_clock.restart();
	double ups_time = 0;
	double fps_time = 0;
	int fps_counter = 0;
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
		delta_time = game_clock.restart().asSeconds();
		ups_time += delta_time;
		fps_time += delta_time;
		if (ups_time > UPDATE_TIME)
		{
			ups_time -= UPDATE_TIME;
			update();	//logic
		}
		if (fps_time >= 1) {
			window->setTitle(TITLE + " | fPS : " + std::to_string(fps_counter));
			fps_time -= 1;
			fps_counter = 0;
		}

		fps_counter++;
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
	player.updateState();
	backgroundManager->updateDayState();
}

void render()
{
	//background
	if(backgroundManager->isDay())
		backgroundManager->drawDay();
	else 
		backgroundManager->drawNight();
	player.updateColor(backgroundManager->getScore());

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
		audioManager.playDie();
		RUNNING = false;
		return;
	}
	//pipes
	for (auto it = backgroundManager->getPipes().begin(); it != backgroundManager->getPipes().end(); it++)
	{
		if (it->intersects(player))
		{
			audioManager.playHit();
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
	player.reset();
	game_clock.restart();
	RUNNING = true;
}