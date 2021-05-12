#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>	
class Platform
{
public:
	Collider GetColider() { return Collider(body); };
	void Draw(sf::RenderWindow& window) { window.draw(body); }
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

private:
	sf::RectangleShape body;
};

