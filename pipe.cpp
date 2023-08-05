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

PipeDirection Pipe::getPipeDirection() { return pipeDirection; }