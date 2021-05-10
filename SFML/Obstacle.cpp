#include "Obstacle.h"
#include "Player.h"
#include <chrono>
#include <thread>

using namespace std;
Obstacle::Obstacle(int speed) 
{
	body.setSize(sf::Vector2f(70.f, 70.f));
	this->speed = speed;
	obstacleTexture2.loadFromFile("photos\\obstacle2.png");
	obstacleTexture1.loadFromFile("photos\\obstacle.png");
	body.setTexture(&obstacleTexture1);
	body.setOrigin(body.getSize() / 2.0f);
	jumpedOver = false;
}


void Obstacle::SetPostion(sf::Vector2f vector,Player& player,sf::RenderWindow& window , Lives* lives)
{
	if (CheckColision(player) && player.invincible == false)
	{
		if (penguinCollision == false)
		{
			lives->DecreaseLives();
			penguinCollision = true;

		}
	}
	if (CheckColision(player))
	{
		body.move({ -200.f , 0 });
	}
	if (clock.getElapsedTime().asMilliseconds() > 3500)
	{
		LoadTextures();
		float y = 343.f;
		if (isWorm == true)
		{
			y += 20;
		}
		body.setPosition(player.GetPosition().x +600.f , y );
		clock.restart();
		jumpedOver = false;
		penguinCollision = false;
		
	}
}
void Obstacle::Draw(sf::RenderWindow& window)
{
	
	window.draw(body);
}
bool Obstacle::CheckColision(Player player)
{
	auto collider = player.GetCollider();
	sf::Vector2f otherPosition = collider.GetPosition();
	sf::Vector2f otherHalfSize = collider.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
	float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);
	if (intersectX < -20.0f && intersectY < 0.0f)
	{
		return true;
	}
	return false;
	auto other = player.GetBody();
	other.setOrigin(other.getSize().x / 2, other.getSize().y / 2);
		
}
void Obstacle::LoadTextures()
{
	int j = rand() % 3;
	if (j == 0)
	{
		obstacleTexture2.loadFromFile("photos\\obstacle2.png");
		obstacleTexture1.loadFromFile("photos\\obstacle.png");
		isWorm = false;
		speed = 200;
	}
	else if (j == 1)
	{
		isWorm = false;
		obstacleTexture2.loadFromFile("photos\\bat1.png");
		obstacleTexture1.loadFromFile("photos\\bat2.png");
		speed = 200;
	}
	else if (j == 2)
	{
		obstacleTexture2.loadFromFile("photos\\skyll-frame1.png");
		obstacleTexture1.loadFromFile("photos\\skyll-frame2.png");
		isWorm = true;
		speed = 250;
	}
}
void Obstacle::Update(float deltaTime)
{
	
	UpdateTexture();
	sf::Vector2f velocity;
	velocity.x = -deltaTime * speed;
	velocity.y = 0;
	body.move(velocity);
}


void Obstacle::UpdateTexture()
{
	
	if (clock2.getElapsedTime().asSeconds() > 0.3)
	{
	
		if (movement == false)
		{
			movement = true;
			body.setTexture(&obstacleTexture1);
		}
		else
		{
			movement = false;
			body.setTexture(&obstacleTexture2);
		}
		clock2.restart();
	}

}
