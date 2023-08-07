#pragma once
#include <SFML\Audio.hpp>

class AudioManager
{
public:
	AudioManager();
	void playHit();
	void playDie();
	void playPoint();
	void playSwoosh();
private:
	sf::SoundBuffer hitBuffer, dieBuffer, pointBuffer, swooshBuffer;
	sf::Sound hit, die, point, swoosh;
};

