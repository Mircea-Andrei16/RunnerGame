#include "Player.h"
#include <thread>          
#include <chrono>  
using namespace std;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, Lives* liv)
	:animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	this->liv = liv;

	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(300.f, 106.0f);
	body.setTexture(texture);

	this->jumpHeight = jumpHeight;

}
void Player::Draw(sf::RenderWindow& window)
{

	window.draw(body);
	if (invincible == true)
	{
		window.draw(circle);
	}

}

sf::Vector2f Player::GetPosition()
{
	return body.getPosition();
}

void Player::Rotate(sf::View& view, int counter)
{
	if (counter == 0)
	{
		view.rotate(5);
	}
}
void Player::Collision(sf::Vector2f direction)
{
	if (direction.x < 0.f)
	{
		velocity.x = 0.f;
	}
	else if (direction.x > 0.f)
	{
		velocity.x = 0.f;
	}
	if (direction.y < 0.f)
	{
		velocity.y = 0;
		canJump = true;
	}
	else if (direction.y > 0.f)
	{
		velocity.y = 0.f;
	}
}
void Player::Update(float deltaTime)
{

	if (clock.getElapsedTime().asSeconds() > 10)
	{
		Invincibility();
		if (clock.getElapsedTime().asSeconds() > 15)
		{
			clock.restart();
			invincible = false;
		}
	}

	velocity.x = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(2.f * 981.f * jumpHeight);
	}
	velocity.y += 981.f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
	}
	if (velocity.x > 0.0f)
		faceRight = true;
	else if (velocity.x < 0.0f)
		faceRight = false;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}
void Player::Invincibility()
{

	circle.setRadius(75.f);
	circle.setPosition(body.getPosition().x - 65, body.getPosition().y - 60);
	invincible = true;
	circle.setFillColor(sf::Color(159, 159, 159, 100));

}
