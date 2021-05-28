#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position,int val)
{
	SetColor(val);
	body.setFillColor(sf::Color(this->red, this->green, this->blue, 255));
	body.setTexture(texture);
	body.setSize(size);
	body.setPosition(position);
	body.setOrigin(size / 2.f);
}

void Platform::SetColor(int val) {

	if (val == 1) {
		this->red = 199;
		this->green = 21;
		this->blue = 133;
	}

	if (val == 2) {
		this->red = 96;
		this->green = 77;
		this->blue = 19;
	}

	if (val == 3) {
		this->red = 89;
		this->green = 26;
		this->blue = 20;
	}

	
}