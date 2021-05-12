#pragma once
#include "SFML/Graphics.hpp"

class MainMenu {

public:
	MainMenu(float witdh, float height);
	~MainMenu();
	void draw(sf::RenderWindow& window);
	void MoveUP();
	void MoveDOWN();
	 
	int GetPressedItem() {
		return selectedItemIndex;
	}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[3];
};