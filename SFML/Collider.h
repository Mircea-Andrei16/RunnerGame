#pragma once
#include "Collider.h"
#include <SFML\Graphics.hpp>
class Collider
{
public:
	void Move(float dx, float dy) { body.move(dx, dy); }
	sf::Vector2f GetPosition() { return  body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	bool checkColision(Collider other,sf::Vector2f &direction, float push);
	Collider(sf::RectangleShape& body);
private:
	sf::RectangleShape& body;
};

