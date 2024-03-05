#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <memory>

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

   

    Player player(300.f, 200.f, 50.f, 0.4f);
    vector<unique_ptr<Enemy>> enemies; // using smart pointers ensures elements are properly deallocated, preventing memory leaks
    try {
        enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f));
        enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.20f)); // give diff speeds to avoid complete overlapping
        enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); 
        //enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); 
        enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.035f)); 
        enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.02f)); 
    }
    catch (const bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return 1; 
    }
    //-------------------------------- INITIALIZE --------------------------------
    player.initialize();
    player.load();
    for (auto& enemy : enemies) {
        enemy->initialize();
        enemy->load();
    }

    // ------------------------------------------ LOAD ---------------------------------

    // Set positions for each entity in the vector
    vector<sf::Vector2f> enemyPositions = {
        sf::Vector2f(1200.f, 600.f), // Soldier1 position
        sf::Vector2f(1300.f, 100.f), // Soldier2 position
        sf::Vector2f(1100.f,351.f), // Skeleton1 position
        //sf::Vector2f(200.0f, 500.0f), // Skeleton2 position
        sf::Vector2f(100.0f, 100.f), // Slime1 position
        sf::Vector2f(1000.0f, 500.0f) // Slime2 position
    };

    for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i]->changePosition(enemyPositions[i].x, enemyPositions[i].y);
    }

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices
    
    GameState state;
    state.loadLevel();

    // ------------------------------- TILEMAP ----------------------------------

    // ---------------------------- TESTING -----------------------------

    /*cout << "Player's size vector is: " << player.getSizeX() << ", " << player.getSizeY() << endl;
    cout << "Soldier's size vector is: " << soldier.getSizeX() << ", " << soldier.getSizeY() << endl;*/
    
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

        for (auto& enemy : enemies) {
            enemy->update(deltaTime, player, player.getSprite().getPosition(), state.CurrentLevel);
            enemy->attackMove(deltaTime, player);
        }

        player.playerUpdate(deltaTime, enemies, mousePosition, state.CurrentLevel); 
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();

        window.draw(state.Map);
        for (const auto& enemy : enemies) {
            enemy->draw(window);
        }
        player.drawPlayer(window);

        enemies.erase( // Some genie code for erasing enemies from the vector
            std::remove_if( // the first parameter of erase; returns an iterator (place to begin erasing) at the dead element (enemy that is dead)
                enemies.begin(),
                enemies.end(),
                [&](const auto& enemy) { return enemy->isDead(enemy); }
            ),
            enemies.end() // the 2nd parameter; tells where to end the erasing
        );
        
        if (player.getHealth() <= 0) {
            break;
        }
        window.display();

        //-------------------------------- DRAW --------------------------------
    }
    cout << "You died! " << endl;

    return 0;
}