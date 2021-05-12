#include "Fire.h"
#include "Player.h"
#include "Enemy.h"
#include <chrono>
#include <thread>
using namespace std;
Fire::Fire(int speed)
{
	body.setSize(sf::Vector2f(70.f, 70.f));
	fireTexture.loadFromFile("photos\\fire.png");
	this->speed = speed;
	body.setTexture(&fireTexture);
	body.setOrigin(body.getSize());
}

void Fire::SetPostion(sf::Vector2f vector, Player& player, sf::RenderWindow& window, sf::RectangleShape body1, Lives* lives)
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
	if (clock.getElapsedTime().asMilliseconds() > 1700)
	{
		body.setPosition(body1.getPosition().x, body1.getPosition().y);
		clock.restart();
		penguinCollision = false;
	}

}

void Fire::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

bool Fire::CheckColision(Player player)
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
}
void Fire::Update(float deltaTime)
{

	sf::Vector2f velocity;
	velocity.x = -deltaTime * speed;
	velocity.y = 0;
	body.move(velocity);
}
