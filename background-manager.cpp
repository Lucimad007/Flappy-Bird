#include "background-manager.h"
#include <string>

extern Player player;

BackgroundManager::BackgroundManager(sf::RenderWindow* inputWindow)
{
	window = inputWindow;
	dayTexture.loadFromFile("assets\\sprites\\background-day.png");
	nightTexture.loadFromFile("assets\\sprites\\background-night.png");
	groundTexture.loadFromFile("assets\\sprites\\base.png");
	daySprite.setTexture(dayTexture);
	nightSprite.setTexture(nightTexture);
	groundSprite.setTexture(groundTexture);
	for (int i = 0; i < 10; i++)
	{
		std::string path = "assets\\sprites\\";
		path += std::to_string(i);
		path += ".png";
		numberTexture[i].loadFromFile(path);
		numberSprite[i].setTexture(numberTexture[i]);
	}
}

void BackgroundManager::drawDay()
{
	int size = dayTexture.getSize().x;
	for (int i = 0; i < window->getSize().x; i += size)
	{
		daySprite.setPosition(sf::Vector2f(i, 0));
		window->draw(daySprite);
	}
	daySprite.setPosition(sf::Vector2f(0, 0));
}

void BackgroundManager::drawNight()
{
	int size = nightTexture.getSize().x;
	for (int i = 0; i < window->getSize().x; i += size)
	{
		nightSprite.setPosition(sf::Vector2f(i, 0));
		window->draw(nightSprite);
	}
	nightSprite.setPosition(sf::Vector2f(0, 0));
}

void BackgroundManager::drawGround()
{
	horizontalOffset -= 0.25f;
	int size = groundTexture.getSize().x;
	if (horizontalOffset <= -size)		//ground moves backward so we think we are moving forward
		horizontalOffset = 0;

	//
	for (double j = 0; j <= ground_y; j += groundTexture.getSize().y / 2)
	{
		for (double i = horizontalOffset - size; i < window->getSize().x; i += size)
		{
			groundSprite.setPosition(sf::Vector2f(i, window->getSize().y - j));
			window->draw(groundSprite);
		}
	}

	//outer layer of ground
	for (double i = horizontalOffset - size; i < window->getSize().x; i += size)
	{
		groundSprite.setPosition(sf::Vector2f(i, window->getSize().y  - ground_y));
		window->draw(groundSprite);
	}

	window->draw(groundSprite);

	groundSprite.setPosition(sf::Vector2f(0, window->getSize().y - groundTexture.getSize().y - ground_y));
}

void BackgroundManager::drawScore()
{
	resetPositionOfNumbers();
	if (score == 0)
	{
		window->draw(numberSprite[0]);
		return;
	}

	int figures = 0;
	int tempScore = score;
	while (tempScore)
	{
		figures++;
		tempScore /= 10;
	}
	
	tempScore = score;
	int figure = 0;
	int last_X = window->getSize().x - scoreGapRelativeToWindow;
	for (int i = 0; i < figures; i++)
	{
		figure = tempScore % 10;
		tempScore /= 10;
		numberSprite[figure].setPosition(last_X - (float)numberTexture[figure].getSize().x, scoreGapRelativeToWindow);
		last_X = numberSprite[figure].getPosition().x;
		window->draw(numberSprite[figure]);
	}
}

void BackgroundManager::resetPositionOfNumbers()
{
	for (int i = 0; i < 10; i++)	//0 - 9
	{
		numberSprite[i].setPosition(window->getSize().x - scoreGapRelativeToWindow, scoreGapRelativeToWindow);		//out of bound enugh!
	}
}

void BackgroundManager::updateScore()
{
	for (auto it = pipes.begin(); it != pipes.end(); ++it)
	{
		if ((!it->getIsPassed()) && (it->getPipeDirection() == DOWN))		//if we count UP pipes it will be twice (wrong)
		{
			if (player.getPosition().x > (it->getPosition().x + it->getSize().x))
			{
				it->setIsPassed(true);
				score++;
			}
		}
	}
}

void BackgroundManager::generatePrimaryPipes()
{	
	Pipe pipeForSize(0, 0, UP);
	for (int i = window->getSize().x / 2; i < window->getSize().x; i += pipeForSize.getSize().x * 3)
	{
		if((int)pipesHeightRelativeToGround % 20)
			pipesHeightRelativeToGround += rand() % 6 * 10;
		else 
			pipesHeightRelativeToGround -= rand() % 6 * 10;

		if (pipesHeightRelativeToGround < 0) 
		{
			pipesHeightRelativeToGround = 0;
		}
		else if (pipesHeightRelativeToGround > window->getSize().y)
		{
			pipesHeightRelativeToGround = window->getSize().y;
		}
		Pipe* pipe = new Pipe(0, 0, DOWN);
		Pipe* pipe2 = new Pipe(0, 0, UP);
		pipe->setPosition(i, window->getSize().y - ground_y - pipesHeightRelativeToGround);
		pipe2->setPosition(i, window->getSize().y - ground_y - pipe->getSize().y - gapBetweenPipes - pipesHeightRelativeToGround);
		pipes.push_back(*pipe);
		pipes.push_back(*pipe2);
	}
}

void BackgroundManager::movePipes(double offset)
{
	for (auto it = pipes.begin(); it != pipes.end(); ++it)
	{
		it->move(-0.25, offset);
	}
}

void BackgroundManager::updatePipes()
{ 
	Pipe lastPipe(0, 0, UP);
	int max_x = 0;

	for (auto it = pipes.begin(); it != pipes.end(); ++it)
	{
		if (it->getPosition().x > max_x)
			max_x = it->getPosition().x;
		if (it->getPosition().x + it->getSize().x < 0)
			it = pipes.erase(it);
	}

	lastPipe.setPosition(sf::Vector2f(max_x, 0));
	//generating new pipes
	if (!pipes.empty())
	{
		if (lastPipe.getPosition().x < window->getSize().x - lastPipe.getSize().x)
		{			
			if ((int)pipesHeightRelativeToGround % 20)
				pipesHeightRelativeToGround += rand() % 6 * 10;
			else
				pipesHeightRelativeToGround -= rand() % 6 * 10;

			if (pipesHeightRelativeToGround < 0)
			{
				pipesHeightRelativeToGround = 0;
			}
			else if (pipesHeightRelativeToGround > window->getSize().y/2)
			{
				pipesHeightRelativeToGround = window->getSize().y/2 - 30;
			}
			Pipe* pipe = new Pipe(lastPipe.getPosition().x + 3 * lastPipe.getSize().x, window->getSize().y - ground_y - pipesHeightRelativeToGround, DOWN);
			Pipe* pipe2 = new Pipe(lastPipe.getPosition().x + 3 * lastPipe.getSize().x, window->getSize().y - ground_y - pipe->getSize().y - gapBetweenPipes - pipesHeightRelativeToGround, UP);
			pipes.push_back(*pipe);
			pipes.push_back(*pipe2);
		}
	}
}

bool BackgroundManager::intersectsGround(double height, double length)
{
	return height + length > window->getSize().y - ground_y;
}

void BackgroundManager::moveGround(double offset)
{
	ground_y += offset;
}

const std::list<Pipe>& BackgroundManager::getPipes() { return pipes; }

double BackgroundManager::getHorizontalOffset() { return horizontalOffset; }
void BackgroundManager::setHorizontalOffset(double offset) { this->horizontalOffset = offset; }