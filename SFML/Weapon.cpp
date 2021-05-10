#include "Weapon.h"

Weapon::Weapon()
{
    
    texture.loadFromFile("photos\\03.png");
    body.setSize(sf::Vector2f(50.f, 50.f));
}

void Weapon::Update(Player player , sf::RenderWindow& window)
{
    body.setTexture(&texture);
    body.setPosition(player.GetPosition().x + 10.f, player.GetPosition().y);
    window.draw(body);
}
