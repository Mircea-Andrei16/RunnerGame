#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(float width, float height) {

	if (!font.loadFromFile("arialbd.ttf")) {
		//handles error
	}

	text[0].setFont(font);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("Choose color for the land:");
	text[0].setPosition(width / 2 - 150, height / (1 + 4) * 1);

	text[1].setFont(font);
	text[1].setFillColor(sf::Color::Red);
	text[1].setString("Color 1: Pink");
	text[1].setPosition(width / 2 - 150, height / (1 + 4) * 2);

	text[2].setFont(font);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("Color 2: Saffron");
	text[2].setPosition(width / 2 - 150, height / (1 + 4) * 3);

	text[3].setFont(font);
	text[3].setFillColor(sf::Color::White);
	text[3].setString("Color 3: Vermilion");
	text[3].setPosition(width / 2 - 150, height / (1 + 4) * 4);

	selectedItem = 0;
}

SettingsWindow::~SettingsWindow(){}

void SettingsWindow::draw(sf::RenderWindow& window) {

	for (int i = 0; i < 4; i++) {
		window.draw(text[i]);
	}
}

void SettingsWindow::moveUp() {
	if (selectedItem - 1 >= 1)
	{
		text[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		text[selectedItem].setFillColor(sf::Color::Red);
	}
}

void SettingsWindow::moveDown() {
	if (selectedItem + 1 < 4)
	{
		text[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		text[selectedItem].setFillColor(sf::Color::Red);
	}
}

int SettingsWindow::setup(sf::RenderWindow& window,int &val) {
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					this->moveUp();
					break;
				case sf::Keyboard::Down:
					this->moveDown();
					break;
				case sf::Keyboard::Escape:
					return 0;
					break;
				case sf::Keyboard::Return:
					switch (this->getPresseditem())
					{
					case 0:
						break;
					case 1:
						return 1;
						break;
					case 2:
						return 2;
						break;
					case 3:
						return 3;
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		this->draw(window);
		window.display();
	}

}