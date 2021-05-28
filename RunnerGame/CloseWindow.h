#pragma once
#include "SFML/Graphics.hpp"

class CloseWindow {
public:
	CloseWindow(float witdh, float height);
	~CloseWindow();
	void draw(sf::RenderWindow& window);
	void setup();
private:
	sf::Text CreditText[3];
	sf::Font font;
};

