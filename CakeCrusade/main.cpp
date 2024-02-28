#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "TileMap.cpp"
#include "Player.hpp"
#include "Soldier.hpp"
#include "Enemy.hpp"

using namespace std; 

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1408, 704), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    Player player(200, 50, 50, 10);
    Soldier soldier(300, 50, 50, 5);
    Enemy enemyA(100, 20, 20, 5);
    //-------------------------------- INITIALIZE --------------------------------
    player.Initialize();
    soldier.Initialize();
    enemyA.Initialize();

    //-------------------------------- INITIALIZE --------------------------------
    
    // ------------------------------------------ LOAD ---------------------------------

    player.Load();
    soldier.Load();
    enemyA.loadTexture("assets/enemies/skelly/idle/skull_idle.png");
    enemyA.Load("assets/enemies/skelly/idle/skull_idle.png");

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices
    int level[] =
    {
        6, 7, 7, 7, 7, 7, 7, 7, 8, 18, 18, 18, 18, 6, 7, 7, 7, 7, 7, 7, 7, 8,
        9, 0, 0, 0, 0, 0, 0, 0, 10, 18, 18, 18, 18, 9, 0, 0, 0, 0, 0, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 2, 3, 14, 7, 7, 7, 7, 15, 0, 0, 0, 0, 0, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 4, 5, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
        9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
        9, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 10,
        9, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 10,
        11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13,
    };

    TileMap map;
    if (!map.load("assets/tilemap/tileset.png", sf::Vector2u(16, 16), level, 22, 11)) 
        return -1;
    // ------------------------------- TILEMAP ----------------------------------
    
    // ---------------------------- TESTING -----------------------------

    cout << "Player's size vector is: " << player.getSizeX() << ", " << player.getSizeY() << endl;
    cout << "Soldier's size vector is: " << soldier.getSizeX() << ", " << soldier.getSizeY() << endl;

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
        player.Update(deltaTime, enemyA, mousePosition, level); // update here
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();
        window.draw(map);
        soldier.Draw(window);
        player.Draw(window);
        enemyA.Draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }

    
    return 0;
}