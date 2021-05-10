#include "Collider.h"
#include <algorithm>
#include <iostream>

bool Collider::checkColision(Collider other,sf::Vector2f& direction, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	float deltaX =  otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
	float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		
		push = std::min(std::max(0.f, push), 1.f);
		if (intersectX > intersectY)
		{
			
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
				direction.x = 1.f;
				direction.y = 0.f;
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
				direction.x = -1.f;
				direction.y = 0.f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f,intersectY * ( 1.0f - push));
				other.Move(0.0f,-intersectY * push);
				direction.x = 0.f;
				direction.y = 1.f;
			}
			else
			{
				Move(0.0f,-intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
				direction.x = 0.f;
				direction.y = -1.f;
			}
			
		}
		return true;
	}

	return false;
}

Collider::Collider(sf::RectangleShape& body): body(body) {}
