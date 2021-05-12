#include "CloseWindow.h"
#include "Audio.h"

CloseWindow::CloseWindow(float width, float height) {

	if (!font.loadFromFile("arialbd.ttf")) {
		//handles error
	}

	CloseText.setFont(font);
	CloseText.setFillColor(sf::Color::Red);
	CloseText.setString("YOU DIED!");
	CloseText.setPosition(width / 2 - 50, height / (1 + 1) * 1);
}

CloseWindow::~CloseWindow() {}

void CloseWindow::draw(sf::RenderWindow& window) {

	window.draw(CloseText);
}


void CloseWindow::setup(sf::RenderWindow& window) {

	Audio audio;
	audio.playDeathSong();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
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