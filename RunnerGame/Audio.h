#pragma once
#include<SFML/Audio.hpp>
class Audio
{
private:
	sf::Sound ZAWARDOO;
	sf::SoundBuffer ZAWARDOOBuffer;
	sf::Sound backroundSong;
	sf::SoundBuffer backroundSongBuffer;
	sf::Sound deathSound;
	sf::SoundBuffer deathSoundBuffer;

public:
	void playZAWARDO();
	void playFundalSong();
	void StopFundalSong();
	void playDeathSong();
	Audio();
};