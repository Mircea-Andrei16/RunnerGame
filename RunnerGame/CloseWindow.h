#pragma once
#include "SFML/Graphics.hpp"

class CloseWindow {
public:
	CloseWindow(float witdh, float height);
	~CloseWindow();
	void draw(sf::RenderWindow& window);
	void setup(sf::RenderWindow& window);
private:
	sf::Text CloseText;
	sf::Font font;
};

