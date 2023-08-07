#include <SFML\Graphics.hpp>
#include "player.h"
#include "background-manager.h"
#include "button.h"
#include "audio-manager.h"
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
void getReady();
void freezeWindow(double seconds);	//the window can be still responsive

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

	getReady();
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
	detectCollisions();
	backgroundManager->movePipes(player.getSpeed());
	backgroundManager->moveGround(player.getSpeed());
	movePlayer();
	backgroundManager->updatePipes();
	player.updateState();
	backgroundManager->updateScore();
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
	player.setSpeed(player.getSpeed() - 0.5 * player.getGravity());
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
	getReady();
}

void getReady()
{
	sf::Texture readyTexture, flappyBirdLogoTexture, number3Texture, number2Texture, number1Texture, birdTexture;
	sf::Sprite bird, logo, ready, number1, number2, number3;
	sf::Color backgroundColor(153, 217, 234);
	int default_x = window->getSize().x/2, default_y = window->getSize().y/2, gap = 80;
	birdTexture.loadFromFile("assets\\sprites\\yellowbird-upflap.png");
	readyTexture.loadFromFile("assets\\sprites\\ready.png");
	flappyBirdLogoTexture.loadFromFile("assets\\sprites\\flappy-bird-logo.png");
	number3Texture.loadFromFile("assets\\sprites\\3.png");
	number2Texture.loadFromFile("assets\\sprites\\2.png");
	number1Texture.loadFromFile("assets\\sprites\\1.png");
	bird.setTexture(birdTexture);
	ready.setTexture(readyTexture);
	logo.setTexture(flappyBirdLogoTexture);
	number3.setTexture(number3Texture);
	number2.setTexture(number2Texture);
	number1.setTexture(number1Texture);
	bird.setPosition(default_x - birdTexture.getSize().x / 2, default_y - 2 * gap);
	logo.setPosition(default_x - flappyBirdLogoTexture.getSize().x/2, default_y - gap);
	ready.setPosition(default_x - readyTexture.getSize().x/2, default_y);
	number3.setPosition(default_x - number3Texture.getSize().x/2, default_y + gap);
	number2.setPosition(default_x - number2Texture.getSize().x/2, default_y + gap);
	number1.setPosition(default_x - number1Texture.getSize().x/2, default_y + gap);
	window->clear(backgroundColor);
	window->draw(number3);
	window->draw(logo);
	window->draw(ready);
	window->draw(bird);
	window->display();
	freezeWindow(1);
	window->clear(backgroundColor);
	window->draw(number2);
	window->draw(logo);
	window->draw(ready);
	window->draw(bird);
	window->display();
	freezeWindow(1);
	window->clear(backgroundColor);
	window->draw(number1);
	window->draw(logo);
	window->draw(ready);
	window->draw(bird);
	window->display();
	freezeWindow(1);
}

void freezeWindow(double seconds)
{
	sf::Event event;
	sf::Clock tempClock;
	double time = 0;

	while (time < seconds)
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		time += tempClock.restart().asSeconds();
	}
}