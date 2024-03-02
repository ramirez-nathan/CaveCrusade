#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "TileMap.hpp"
#include "Player.hpp"
#include "Soldier.hpp"
#include "Enemy.hpp"
#include "GameState.hpp"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1408, 704), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    Player player(200, 50, 50, 10);
    Soldier soldier(300, 50, 50, 0.1);
    Enemy enemyA(100, 20, 20, 0.05);
    Enemy slimey(50, 10, 5, 0.02);
    //-------------------------------- INITIALIZE --------------------------------
    player.Initialize();
    soldier.Initialize();
    enemyA.Initialize();
    slimey.Initialize();

    //-------------------------------- INITIALIZE --------------------------------

    // ------------------------------------------ LOAD ---------------------------------

    player.Load();
    soldier.Load();
    enemyA.loadTexture("assets/enemies/skelly/idle/skull_idle.png");
    enemyA.Load();
    slimey.loadTexture("assets/enemies/Slime/slime_idle.png");
    slimey.Load();
    enemyA.changePosition(200.0f, 500.0f);
    slimey.changePosition(1000.0f, 500.0f);

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices
    
    GameState state;
    state.loadLevel();

    // ------------------------------- TILEMAP ----------------------------------

    // ---------------------------- TESTING -----------------------------

    cout << "Player's size vector is: " << player.getSizeX() << ", " << player.getSizeY() << endl;
    cout << "Soldier's size vector is: " << soldier.getSizeX() << ", " << soldier.getSizeY() << endl;
    player.attackMove();

    // ---------------------------- TESTING -----------------------------

    // ------------------------------------------ LOAD ---------------------------------
    sf::Clock clock;
    //main game loop
    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;
        //-------------------------------- UPDATE --------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        soldier.Update(deltaTime, player.getSprite().getPosition(), level);
        enemyA.Update(deltaTime, player.getSprite().getPosition(), level);
        slimey.Update(deltaTime, player.getSprite().getPosition(), level);
        player.Update(deltaTime, enemyA, mousePosition, level); // update here
        soldier.update(deltaTime, player.getSprite().getPosition(), state.CurrentLevel);
        player.update(deltaTime, soldier, mousePosition, state.CurrentLevel); // update here
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();
        window.draw(map);
        soldier.Draw(window);
        player.Draw(window);
        enemyA.Draw(window);
        slimey.Draw(window);
        window.draw(state.Map);
        soldier.drawSoldier(window);
        player.drawPlayer(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }


    return 0;
}