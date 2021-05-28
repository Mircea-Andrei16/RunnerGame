#include "Game.h"
#include "CloseWindow.h"

void Game::ConfigureGame(sf::RenderWindow &window,int val)
{
    sf::Texture playerTexture;

    Lives* lives = new Lives();

    sf::FloatRect   fBounds(-0.f, -0.f, 5500.f, 5000.f);
    sf::Texture     Texture;

    Texture.loadFromFile("photos\\4.png");
    sf::IntRect        iBounds(fBounds);
    Texture.setRepeated(true);
    sf::Sprite         Sprite(Texture, iBounds);

    const sf::Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
    const sf::Vector2f spriteStart(fBounds.left-10, fBounds.top+380);


    sf::Text text;
    text.setFillColor(sf::Color::Red);
    text.setString("You died!");

    srand(time(NULL));

    playerTexture.loadFromFile("photos\\runner.png");
    Player player(&playerTexture, sf::Vector2u(5, 2), 0.3f, 100.0f, 200.0f, lives);


    float deltaTime = 0.0f;

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(650.0f, 650.0f));
    
    sf::Clock clock;

    Obstacle obstacle1(200);
    Enemy enemy1;
    
    Fire fire1(350);

    Audio playEffectSound;

   // playEffectSound.playFundalSong();

    int counterSounds = 0;

    Score score;

    
    while (window.isOpen())
    {
       deltaTime = clock.getElapsedTime().asSeconds();

        if (deltaTime > 1.f / 20.f)
        {
            deltaTime = 1.f / 20.f;
        }
        
        Platform platform(nullptr, sf::Vector2f(1200.f, 250.f), sf::Vector2f(player.GetPosition().x, 500.f), val);
        Platform platform1(nullptr, sf::Vector2f(50.f, 20.f), sf::Vector2f(500.f, 200.f), val);
        Platform platform2(nullptr, sf::Vector2f(50.f, 20.f), sf::Vector2f(1200.f, 280.f), val);
       

        clock.restart();
       
        sf::Event evnt;

        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }

        }

        player.Update(deltaTime);

        sf::Vector2f vector(player.GetPosition().x + 500.f, player.GetPosition().y + 220);
        
        obstacle1.SetPostion(sf::Vector2f(vector.x, 350.f), player, window, lives);

        enemy1.SetPostion(sf::Vector2f(vector.x, 350.f), player, window, fire1, lives);

        sf::Vector2f direction;

        if (platform.GetColider().checkColision(player.GetCollider(), direction, 1.f))
        {
            player.Collision(direction);
        }

        if (platform1.GetColider().checkColision(player.GetCollider(), direction, 1.f))
        {
            player.Collision(direction);
        }

        if (platform2.GetColider().checkColision(player.GetCollider(), direction, 1.f))
        {
            player.Collision(direction);
        }

        view.move(10.2f, 5.0f);
        const sf::Vector2f viewOffset(viewStart - view.getCenter());
        sf::Vector2f spriteOffset;
        spriteOffset.x = floor(viewOffset.x / Texture.getSize().x) * Texture.getSize().x;
        spriteOffset.y = floor(viewOffset.y / Texture.getSize().y) * Texture.getSize().y;
        Sprite.setPosition(spriteStart - spriteOffset);
       
        window.clear(sf::Color(10, 191, 255));
        window.setView(view);
        window.draw(Sprite);

        view.setCenter(player.GetPosition().x + 250.f, player.GetPosition().y);
        window.setView(view);

        score.Update(player);
        lives->UpdateLives(player);
        obstacle1.Update(deltaTime);
        fire1.Update(deltaTime);

        player.Draw(window);
        score.Draw(window);
        obstacle1.Draw(window);
        enemy1.Draw(window);

        lives->DrawLives(window);

        fire1.Draw(window);

        platform.Draw(window);
        platform2.Draw(window);
        platform1.Draw(window);

        window.display();
        score.IncreaseScore(player, obstacle1, enemy1);
    }

}
