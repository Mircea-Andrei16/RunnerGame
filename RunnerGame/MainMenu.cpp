#include "MainMenu.h"


MainMenu::MainMenu(float width, float height) {

	if (!font.loadFromFile("arialbd.ttf")) {
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 - 50, height / (4 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Credits");
	menu[1].setPosition(sf::Vector2f(width / 2 - 50, height / (4 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Settings");
	menu[2].setPosition(sf::Vector2f(width / 2 - 50, height / (4 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Black);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - 50, height / (4 + 1) * 4));

	selectedItemIndex = 0;
}

MainMenu::~MainMenu() {}

void MainMenu::draw(sf::RenderWindow& window) {

	for (int i = 0; i < 4; i++) {

		window.draw(menu[i]);
	}
}

void MainMenu::MoveUP() {

	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDOWN() {

	if (selectedItemIndex + 1 < 4)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}