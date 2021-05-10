#pragma once
#include<SFML/Audio.hpp>
class Audio
{
private:
	sf::Sound maybeNextTime;
	sf::SoundBuffer maybeNextTimeBuffer;
	sf::Sound backroundSong;
	sf::SoundBuffer backroundSongBuffer;
public:
	void playZAWARDO();
	void playFundalSong();
	Audio();
};