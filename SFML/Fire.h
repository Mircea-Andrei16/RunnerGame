#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Lives.h"
class Fire
{
public:
	Fire(int speed);
	void SetPostion(sf::Vector2f, Player& play, sf::RenderWindow& window,  sf::RectangleShape body1, Lives* liv);
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	bool CheckColision(Player player);
	sf::Vector2f GetPosition() { return  body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

	bool penguinCollision = false;
private:
	sf::RectangleShape body;
	int speed;
	bool movement = false;
	sf::Texture fireTexture;
	sf::Clock clock;
	sf::Clock clock2;



};


