#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "TileMap.cpp"
#include "Player.hpp"
#include "Soldier.hpp"

using namespace std; 

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1408, 704), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    Player player(200, 25);
    Soldier soldier(75, 50);
    //-------------------------------- INITIALIZE --------------------------------
    player.Initialize();
    soldier.Initialize();

    //-------------------------------- INITIALIZE --------------------------------
    
    // ------------------------------------------ LOAD ---------------------------------

    player.Load();
    soldier.Load();

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices
    const int level[] =
    {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 4, 5, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 1,
        1, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    };
    TileMap map;
    if (!map.load("assets/tilemap/tileset.png", sf::Vector2u(16, 16), level, 22, 11)) 
        return -1;
    // ------------------------------- TILEMAP ----------------------------------
    
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

        soldier.Update(deltaTime);
        player.Update(deltaTime, soldier, mousePosition);
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();
        window.draw(map);
        soldier.Draw(window);
        player.Draw(window);
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    
    return 0;
}