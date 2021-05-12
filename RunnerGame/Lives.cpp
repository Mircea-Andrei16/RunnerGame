#include "Lives.h"
#include "Audio.h"
#include "CreditWindow.h"

bool Lives::DrawLives(sf::RenderWindow& window)
{
	if (lives == 0)
	{
		return false;
	}
	for (int i = 1; i <= lives; i++)
	{
		window.draw(hearts[i - 1]);
	}
	return true;
}
void Lives::UpdateLives(Player& player)
{

	for (int i = 1; i <= lives; i++)
	{
		sf::RectangleShape heart1;
		heart1.setSize({ 50.f, 50.f });
		hearts.push_back(heart1);
	}

	heartTexture.loadFromFile("heart.png");
	for (int i = 1; i <= lives; i++)
	{
		if (i == 1)
		{
			hearts[i - 1].setPosition(player.GetPosition().x + 500.f, player.GetPosition().y - 300.f);
		}
		else
		{
			hearts[i - 1].setPosition(hearts[i - 2].getPosition().x - 60.f, hearts[i - 2].getPosition().y);
		}
		hearts[i - 1].setTexture(&heartTexture);
	}

}