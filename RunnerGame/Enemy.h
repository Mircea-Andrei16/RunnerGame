#pragma once
#include "Fire.h"
#include "Lives.h"
class Enemy
{
public:
	Enemy();
	void SetPostion(sf::Vector2f, Player& play, sf::RenderWindow& window, Fire& f, Lives* liv);
	void Draw(sf::RenderWindow& window);
	bool CheckColision(Player player);
	sf::Vector2f GetPosition() { return  body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	bool jumpedOver = false;
	bool runnerCollision = false;

private:
	sf::RectangleShape body;
	bool movement = false;
	sf::Texture enemyTexture;
	sf::Clock clock;
	sf::Clock clock2;
};
