#pragma once
#include "SFML/Graphics.hpp"

class CreditWindow{
public:
	CreditWindow(float witdh, float height);
	~CreditWindow();
	void draw(sf::RenderWindow& window);
	void setup(sf::RenderWindow& window);
private:
	sf::Text CreditText[3];
	sf::Font font;
};

