#include "pipe.h"

Pipe::Pipe(double x, double y,PipeDirection direction, PipeColor pipeColor)
{
	this->pipeColor = pipeColor;
	pipeDirection = direction;
	this->setPosition(x, y);
	if (pipeColor == GREEN_PIPE)
	{
		if (direction == UP)
		{
			pipeTexture.loadFromFile("assets\\sprites\\pipe-green-up.png");
		}
		else if (direction == DOWN)
		{
			pipeTexture.loadFromFile("assets\\sprites\\pipe-green-down.png");
		}
	}
	else if (pipeColor == RED_PIPE)
	{
		if (direction == UP)
		{
			pipeTexture.loadFromFile("assets\\sprites\\pipe-red-up.png");
		}
		else if (direction == DOWN)
		{
			pipeTexture.loadFromFile("assets\\sprites\\pipe-red-down.png");
		}
	}
	this->setSize(sf::Vector2f(pipeTexture.getSize().x, pipeTexture.getSize().y));
	this->setTexture(&pipeTexture);
}

Pipe::Pipe(const Pipe& input) :
	sf::RectangleShape(input)	//here we can initialize bas class correctly
{
	this->pipeTexture = input.pipeTexture;
	this->pipeDirection = input.pipeDirection;
	this->pipeColor = input.pipeColor;
	this->isPassed = input.isPassed;
}

bool Pipe::intersects(const Player& player) const
{
	bool y_intersects = false, x_intersects = false;
	double x1, x2, y1, y2, x_len1, x_len2, y_len1, y_len2;
	x1 = this->getPosition().x;
	x2 = player.getPosition().x;
	y1 = this->getPosition().y;
	y2 = player.getPosition().y;
	x_len1 = this->getSize().x;
	x_len2 = player.getSize().x;
	y_len1 = this->getSize().y;
	y_len2 = player.getSize().y;

	if ((x1 < x2 + x_len2) && (x1 > x2))
		x_intersects = true;
	if ((y1 < y2 + y_len2) && (y1 > y2))
		y_intersects = true;
	if ((x2 < x1 + x_len1) && (x2 > x1))
		x_intersects = true;
	if ((y2 < y1 + y_len1) && (y2 > y1))
		y_intersects = true;

	return x_intersects && y_intersects;
}

PipeDirection Pipe::getPipeDirection() { return pipeDirection; }

void Pipe::setIsPassed(bool isPassed) { this->isPassed = isPassed; }

bool Pipe::getIsPassed() { return isPassed; }

PipeColor Pipe::getPipeColor() { return pipeColor; }

sf::RectangleShape Pipe::getGreenShaft()
{
	return greenShaft;
}

sf::RectangleShape Pipe::getRedShaft()
{
	return redShaft;
}