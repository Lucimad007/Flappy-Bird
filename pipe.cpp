#include "pipe.h"

Pipe::Pipe(int x, int y,PipeDirection direction)
{
	pipeDirection = direction;
	this->setPosition(x, y);
	if (direction == UP)
	{
		pipeTexture.loadFromFile("assets\\sprites\\pipe-green-up.png");
	}
	else if (direction == DOWN)
	{
		pipeTexture.loadFromFile("assets\\sprites\\pipe-green-down.png");
	}
	this->setSize(sf::Vector2f(pipeTexture.getSize().x, pipeTexture.getSize().y));
	this->setTexture(&pipeTexture);
}

Pipe::Pipe(const Pipe& input) :
	sf::RectangleShape(input)	//here we can initialize bas class correctly
{
	this->pipeTexture = input.pipeTexture;
	this->pipeDirection = input.pipeDirection;
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