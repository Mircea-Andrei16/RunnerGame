#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "Collider.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Score.h"
#include "Fire.h"
#include "Audio.h"
#include <vector>
#include "Lives.h"
#include "Game.h"
#include "MainMenu.h"
#include "CreditWindow.h"
#include "SettingsWindow.h"

int main()
{
    Game game;

    sf::RenderWindow window(sf::VideoMode(1000, 896), "THE RUNNER", sf::Style::Default | sf::Style::Resize | sf::Style::Close);
   
    sf::Texture texture;
    texture.loadFromFile("photos\\background.png");
    sf::Sprite sprite(texture);

    sf::Image icon;
    icon.loadFromFile("photos\\icon.png");
    window.setIcon(710, 599, icon.getPixelsPtr());

    MainMenu menu(window.getSize().x, window.getSize().y);
    CreditWindow creditWindow(window.getSize().x, window.getSize().y);
    SettingsWindow settingsWindow(window.getSize().x, window.getSize().y);

    int val = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUP();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDOWN();
                    break;
                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem()) 
                    {
                    case 0:
                        game.ConfigureGame(window,val);
                        break;
                    case 1:
                        creditWindow.setup(window);
                        break;
                    case 2:
                        val = settingsWindow.setup(window,val);
                        break;
                    case 3:
                        window.close();
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
        window.draw(sprite);
        menu.draw(window);
        window.display();
    }   
    return 0;
}