#pragma once
#include "Obstacle.h"
#include "Enemy.h"
class Score
{
public:
	void IncreaseScore(Player player, Obstacle& obstacle , Enemy &enemy);
	int GetScore() { return score; }
	Score();
	void Update(Player player);
	void Draw(sf::RenderWindow& window);
private:
	int score = 0;
	sf::Text TextScore;
	sf::Font arial;

};

