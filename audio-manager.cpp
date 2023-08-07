#include "audio-manager.h"

AudioManager::AudioManager()
{
	pointBuffer.loadFromFile("assets\\audio\\point.wav");
	dieBuffer.loadFromFile("assets\\audio\\die.wav");
	swooshBuffer.loadFromFile("assets\\audio\\swoosh.wav");
	hitBuffer.loadFromFile("assets\\audio\\hit.wav");
	hit.setBuffer(hitBuffer);
	die.setBuffer(dieBuffer);
	swoosh.setBuffer(swooshBuffer);
	point.setBuffer(pointBuffer);
}

void AudioManager::playHit()
{
	hit.stop();
	hit.play();
}
void AudioManager::playDie()
{
	die.stop();
	die.play();
}
void AudioManager::playPoint()
{
	point.stop();
	point.play();
}
void AudioManager::playSwoosh()
{
	swoosh.stop();
	swoosh.play();
}