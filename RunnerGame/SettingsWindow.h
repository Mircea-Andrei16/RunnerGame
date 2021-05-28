#pragma once
#include <SFML/Graphics.hpp>


class SettingsWindow {

public:
	SettingsWindow(float witdh, float height);
	~SettingsWindow();
	void draw(sf::RenderWindow& window);
	int setup(sf::RenderWindow& window,int &val);
	void moveUp();
	void moveDown();
	int getPresseditem() {
		return selectedItem;
	}

private:
	sf::Text text[4];
	sf::Font font;  
	int selectedItem;
};
