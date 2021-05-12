#include "Enemy.h"
#include "Player.h"

#include <chrono>
#include <thread>
using namespace std;
Enemy::Enemy()
{
	body.setSize(sf::Vector2f(50.f, 50.f));
	enemyTexture.loadFromFile("photos\\enemy.png");
	body.setTexture(&enemyTexture);
	body.setOrigin(body.getSize() / 2.0f);
}

void Enemy::SetPostion(sf::Vector2f vector, Player& player, sf::RenderWindow& window, Fire& fire, Lives* lives)
{
	if (CheckColision(player) && player.invincible == false)
	{
		if (runnerCollision == false)
		{
			lives->DecreaseLives();
			runnerCollision = true;

		}
	}
	if (CheckColision(player))
	{
		body.move({ -200.f , 0 });
	}
	if (clock.getElapsedTime().asMilliseconds() > 8000 && player.GetPosition().x > body.getPosition().x)
	{
		body.setPosition(player.GetPosition().x + 500.f, 350.f);
		clock.restart();
		jumpedOver = false;
		runnerCollision = false;

	}
	if (clock.getElapsedTime().asMilliseconds() > 8000)
	{
		clock.restart();
	}
	fire.SetPostion({ body.getPosition().x , 450.f }, player, window, body, lives);

}
void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
bool Enemy::CheckColision(Player player)
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



