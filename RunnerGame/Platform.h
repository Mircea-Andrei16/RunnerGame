#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>	
class Platform
{
public:
	Collider GetColider() { return Collider(body); };
	void Draw(sf::RenderWindow& window) { window.draw(body); }
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position,int val);
	void SetColor(int val);

private:
	sf::RectangleShape body;
	int red = 205;
	int green = 133;
	int blue = 63;
};

