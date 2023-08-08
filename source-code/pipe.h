#pragma once
#include <SFML\Graphics.hpp>
#include "player.h"

enum PipeDirection {UP, DOWN};
enum PipeColor {GREEN_PIPE, RED_PIPE};

class Pipe : public sf::RectangleShape
{
public:
	Pipe(int x, int y, PipeDirection direction, PipeColor pipeColor);
	Pipe(const Pipe&);		//do not forget to implement that because we are inheritancing another class and we might encounter problems when our code need copy constructor , like std::list<Pipe> scenario
	PipeDirection getPipeDirection();
	bool intersects(const Player& player) const;
	void setIsPassed(bool isPassed);
	bool getIsPassed();
	PipeColor getPipeColor();
	static sf::RectangleShape getGreenShaft();
	static sf::RectangleShape getRedShaft();
private :
	sf::Texture pipeTexture;
	PipeDirection pipeDirection = DOWN;
	bool isPassed = false;
	PipeColor pipeColor;
public:
	static sf::Texture redShaftTexture, greenShaftTexture;
	static sf::RectangleShape redShaft, greenShaft;
};

