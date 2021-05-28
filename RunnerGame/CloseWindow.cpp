#include "CloseWindow.h"
#include "Audio.h"

CloseWindow::CloseWindow(float width, float height) {

	if (!font.loadFromFile("arialbd.ttf")) {
		//handles error
	}

	CreditText[0].setFont(font);
	CreditText[0].setFillColor(sf::Color::White);
	CreditText[0].setString("");
	CreditText[0].setPosition(width / 2, height / (1 + 3) * 1);

	CreditText[1].setFont(font);
	CreditText[1].setFillColor(sf::Color::Red);
	CreditText[1].setString("     You died!                   ");
	CreditText[1].setPosition(width / 2-100, height / (1 + 3) * 1);

	CreditText[2].setFont(font);
	CreditText[2].setFillColor(sf::Color::Red);
	CreditText[2].setString("");
	CreditText[2].setPosition(width / 2-100, height / (1 + 3) * 2);
}

CloseWindow::~CloseWindow() {}

void CloseWindow::draw(sf::RenderWindow& window) {

	for (int i = 0; i< 3; i++) {
		window.draw(CreditText[i]);
	}
}


void CloseWindow::setup() {

	sf::RenderWindow window(sf::VideoMode(1000, 896), "THE RUNNER", sf::Style::Default | sf::Style::Resize | sf::Style::Close);

	sf::Texture texture;
	texture.loadFromFile("photos\\background.png");
	sf::Sprite sprite(texture);

	sf::Image icon;
	icon.loadFromFile("photos\\icon.png");
	window.setIcon(710, 599, icon.getPixelsPtr());


	while (window.isOpen())
	{
		sf::Event event;


		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
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