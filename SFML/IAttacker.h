#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class IAttacker
{
public:
	virtual void SetPostion(sf::Vector2f vector, Player player, sf::RenderWindow& window);
	virtual void Draw(sf::RenderWindow& window);
	virtual bool CheckColision(Player player);
	virtual void Update(float deltaTime);
	virtual void UpdateTexture();
	virtual sf::Vector2f GetPosition() { return  body.getPosition(); }
	virtual sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	IAttacker(int speed);
private:

	 sf::RectangleShape body;
	bool set = false;
	int speed = 200;
	bool movement = false;
	sf::Texture obstacleTexture1;
	sf::Texture obstacleTexture2;
	sf::Clock clock;
	sf::Clock clock2;
};

