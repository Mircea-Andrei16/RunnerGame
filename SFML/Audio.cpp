#include"Audio.h"
#include <iostream>

Audio::Audio()
{	
	this->maybeNextTimeBuffer.loadFromFile("audio\\ZA WARUDO.wav");
	this->backroundSongBuffer.loadFromFile("audio\\JoJo.wav");
}
void Audio::playZAWARDO()
{
	this->maybeNextTime.setBuffer(this->maybeNextTimeBuffer);
	this->maybeNextTime.setVolume(70.0f);
	this->maybeNextTime.play();
}
void Audio::playFundalSong()
{
	this->backroundSong.setBuffer(this->backroundSongBuffer);
	this->backroundSong.setVolume(20);
	this->backroundSong.play();

}