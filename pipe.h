#pragma once
#include <SFML\Graphics.hpp>

enum PipeDirection {UP, DOWN};

class Pipe : public sf::RectangleShape
{
public:
	Pipe(int x, int y, PipeDirection direction);
	Pipe(const Pipe&);		//do not forget to implement that because we are inheritancing another class and we might encounter problems when our code need copy constructor , like std::list<Pipe> scenario
	PipeDirection getPipeDirection();
private :
	sf::Texture pipeTexture;
	PipeDirection pipeDirection = DOWN;
};

