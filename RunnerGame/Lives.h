#pragma once
#include "Player.h"
#include <thread>          
#include <chrono>  

class Audio;
using namespace std;
class Lives
{
public:
	bool DrawLives(sf::RenderWindow& window);
	void UpdateLives(Player& player);
	void DecreaseLives() { lives--; }
private:
	int lives = 5;
	std::vector<sf::RectangleShape> hearts;
	sf::Texture heartTexture;
};

