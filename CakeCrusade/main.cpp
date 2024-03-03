#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "TileMap.hpp"
#include "Player.hpp"
#include "Soldier.hpp"
#include "Enemy.hpp"
#include "Slime.hpp"
#include "Skeleton.hpp"
#include "GameState.hpp"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1408, 704), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    Player player(200.f, 50.f, 50.f, 0.4f);
    Soldier soldier(200.f, 50.f, 50.f, 0.15f);
    Skeleton skeleton(150.f, 20.f, 20.f, 0.075f);
    Slime slime(300.f, 10.f, 5.f, 0.035f);
    //Enemy soldier2(300.f, 50.f, 50.f, 0.15f);
    //-------------------------------- INITIALIZE --------------------------------
    player.initialize();
    soldier.initialize();
    skeleton.initialize();
    slime.initialize();
    //soldier2.initialize();

    // ------------------------------------------ LOAD ---------------------------------
    player.load();
    soldier.loadTexture("assets/enemies/evil_soldier/textures/evil_soldier_idle.png");
    soldier.load();
    skeleton.loadTexture("assets/enemies/skelly/idle/skull_idle.png");
    skeleton.load();
    slime.loadTexture("assets/enemies/Slime/slime_idle.png");
    slime.load();
    //soldier2.loadTexture("assets/enemies/evil_soldier/textures/evil_soldier_idle.png");
    //soldier2.load();
    soldier.changePosition(1200.f, 600.f);
    skeleton.changePosition(200.0f, 500.0f);
    slime.changePosition(1000.0f, 500.0f);
    //soldier2.changePosition(250.f, 100.f);
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

        soldier.update(deltaTime, player.getSprite().getPosition(), state.CurrentLevel);
        skeleton.update(deltaTime, player, player.getSprite().getPosition(), state.CurrentLevel);
        slime.update(deltaTime, player.getSprite().getPosition(), state.CurrentLevel);
        //soldier2.update(deltaTime, player.getSprite().getPosition(), state.CurrentLevel);
        player.update(deltaTime, soldier, skeleton, slime, mousePosition, state.CurrentLevel); 
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();

        window.draw(state.Map);
        soldier.draw(window);
        skeleton.draw(window);
        slime.draw(window);
        //soldier2.draw(window);
        player.drawPlayer(window);

        if (player.getHealth() <= 0) {
            break;
        }
        window.display();

        //-------------------------------- DRAW --------------------------------
    }
    cout << "You died! " << endl;

    return 0;
}