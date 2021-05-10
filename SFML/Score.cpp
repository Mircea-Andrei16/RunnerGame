#include "Score.h"

Score::Score()
{
	
	arial.loadFromFile("arialbd.ttf");
	TextScore.setPosition({ 10 , 10 });
	TextScore.setFont(arial);
	TextScore.setFillColor(sf::Color::Black);
	
}
void Score::IncreaseScore(Player player, Obstacle& obstacle,Enemy& enemy)
{
	if ((player.GetPosition().x > obstacle.GetPosition().x) && (obstacle.jumpedOver == false) && obstacle.GetPosition().x > 0 && obstacle.penguinCollision == false)
	{
		obstacle.jumpedOver = true;
		score++;
	}
	if ((player.GetPosition().x > enemy.GetPosition().x) && (enemy.jumpedOver == false) && enemy.GetPosition().x > 0 && enemy.penguinCollision == false)
	{
		enemy.jumpedOver = true;
		score++;
	}
}
void Score::Update(Player player)
{
	
	TextScore.setFont(arial);
	std::string s = "Score:";
	s += std::to_string(score);
	TextScore.setString(s);
	TextScore.setPosition(player.GetPosition().x - 60.f, player.GetPosition().y - 310.f);

}
void Score::Draw(sf::RenderWindow& window)
{
	window.draw(TextScore);
}