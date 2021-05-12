#include "CreditWindow.h"


CreditWindow::CreditWindow(float width,float height){

	if (!font.loadFromFile("arialbd.ttf")) {
		//handles error
	}

	CreditText[0].setFont(font);
	CreditText[0].setFillColor(sf::Color::White);
	CreditText[0].setString("In 2021 this game was made by:");
	CreditText[0].setPosition(width / 2 - 150, height / (1 + 3) * 1);

	CreditText[1].setFont(font);
	CreditText[1].setFillColor(sf::Color::White);
	CreditText[1].setString("Pomacu Mircea-Andrei");
	CreditText[1].setPosition(width / 2 - 150, height / (1 + 3) * 2);

	CreditText[2].setFont(font);
	CreditText[2].setFillColor(sf::Color::White);
	CreditText[2].setString("Radut Michelle-Gabriela");
	CreditText[2].setPosition(width / 2 - 150, height / (1 + 3) * 3);
}

CreditWindow::~CreditWindow(){}

void CreditWindow::draw(sf::RenderWindow& window) {

	for (int i = 0; i < 3; i++) {
		window.draw(CreditText[i]);
	}
}


void CreditWindow::setup(sf::RenderWindow& window) {
   
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {  
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					return;
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