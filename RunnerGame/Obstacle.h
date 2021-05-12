#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include"Lives.h"
class Obstacle
{
public:
	Obstacle(int speed);
	void SetPostion(sf::Vector2f, Player& play, sf::RenderWindow& window, Lives* liv);
	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);
	void UpdateTexture();
	bool CheckColision(Player player);
	sf::Vector2f GetPosition() { return  body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	bool jumpedOver = false;
	void LoadTextures();
	bool runnerCollision = false;
private:
	sf::RectangleShape body;
	int speed;
	bool movement = false;
	sf::Texture obstacleTexture1;
	sf::Texture obstacleTexture2;
	sf::Clock clock;
	sf::Clock clock2;
	bool isWorm = false;

};
