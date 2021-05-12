#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setFillColor(sf::Color(205, 133, 63, 200));
	body.setTexture(texture);
	body.setSize(size);
	body.setPosition(position);
	body.setOrigin(size / 2.f);
}
