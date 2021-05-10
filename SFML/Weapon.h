#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Weapon
{
public:
	Weapon();
	void Update(Player player,sf::RenderWindow&window);
private:
	sf::RectangleShape body;
	sf::Texture texture;
};

