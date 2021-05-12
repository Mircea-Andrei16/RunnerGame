#include"Audio.h"
#include <iostream>

Audio::Audio()
{
	this->ZAWARDOOBuffer.loadFromFile("audio\\ZA WARUDO.wav");
	this->backroundSongBuffer.loadFromFile("audio\\JoJo.wav");
	this->deathSoundBuffer.loadFromFile("audio\\OH MY GOD.wav");
}
void Audio::playZAWARDO()
{
	this->ZAWARDOO.setBuffer(this->ZAWARDOOBuffer);
	this->ZAWARDOO.setVolume(70.0f);
	this->ZAWARDOO.play();
}
void Audio::playFundalSong()
{
	this->backroundSong.setBuffer(this->backroundSongBuffer);
	this->backroundSong.setVolume(20);
	this->backroundSong.play();
}

void Audio::playDeathSong() {

	this->deathSound.setBuffer(this->deathSoundBuffer);
	this->deathSound.setVolume(80);
	this->deathSound.play();
}

void Audio::StopFundalSong() {

	this->backroundSong.stop();
 }
