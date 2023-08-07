#pragma once
#include <SFML\Graphics.hpp>

enum BirdColor {RED_BIRD, YELLOW_BIRD, BLUE_BIRD};
enum BirdState {UP_WING, MID_WING, DOWN_WING};

class Player : public sf::RectangleShape
{
public:
	Player(int x = 0, int y = 0, int speed = 0);

	double getSpeed();
	void setSpeed(double speed);
	double getGravity();
	void flap();
	void setYellowColor();
	void setBlueColor();
	void setRedColor();
	void updateColor(int score);
	void updateState();
	void reset();


private:
	const int width = 32;
	const int height = 32;
	const int SPECIAL_SCORE = 1000;		//the bird will stay red
	double speed;		//vertical speed
	const double gravity = 0.4;
	const double flapSpeed = 2.5;
	sf::Texture yellowTextureUp, redTextureUp, blueTextureUp, yellowTextureDown, redTextureDown, blueTextureDown, yellowTextureMid, redTextureMid, blueTextureMid;
	BirdColor birdColor = YELLOW_BIRD;
	BirdState birdState = UP_WING;
public:
	static double X_INIT, Y_INIT;
	static int SPEED_INIT;
};

