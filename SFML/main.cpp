#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "Weapon.h"
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
int main()
{
    Game game;
    game.ConfigureGame();
    return 0;
}