#pragma once
#include "Animation.h"
#include "Collider.h"
class Lives;

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, Lives* liv);
	void Update(float deltaTime);
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow& window);
	void Rotate(sf::View& view, int counter);
	Collider GetCollider() { return Collider(body); };
	void Collision(sf::Vector2f direction);
	sf::RectangleShape GetBody() { return body; }
	void Invincibility();
	bool invincible = false;
	Lives* liv;
private:
	float speed;
	unsigned int row;
	Animation animation;
	sf::RectangleShape body;
	bool faceRight;
	sf::Vector2f velocity;
	float jumpHeight;
	bool canJump;
	sf::CircleShape circle;
	sf::Clock clock;
};

