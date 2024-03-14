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
#include "Knight.hpp"
#include "GameState.hpp"
#include "SoundFx.hpp"
#include "Interactable.hpp"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1472, 896), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);
    auto icon = sf::Image();
    if (!icon.loadFromFile("assets/icon.png"))
    {
        std::cerr << "Failed to load icon from " << "assets/icon.png" << std::endl;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Player player(3000.f, 50.f, 150.f, 0.4f);
    vector<unique_ptr<Enemy>> enemies; // using smart pointers ensures elements are properly deallocated, preventing memory leaks
    try {
        enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 40.0f));
        enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.20f, 40.0f)); // give diff speeds to avoid complete overlapping
        enemies.push_back(make_unique<Knight>(200.0f, 50.0f, 50.0f, 0.1f, 50.0f));
        //enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); 
        //enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); 
        //enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.15f)); 
        //enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.02f)); */ 
    }
    catch (const bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        return 1;
    }
    vector<Interactable> interactables;

    //-------------------------------- INITIALIZE --------------------------------
    player.initialize();
    player.load();
    for (auto& enemy : enemies) {
        enemy->initialize();
        enemy->load();
    }

    // ------------------------------------------ LOAD ---------------------------------

    // Set positions for each entity in the vector 
    vector<sf::Vector2f> enemyPositions1a = {
        sf::Vector2f(360.f, 411.f), // Soldier1 position 
        sf::Vector2f(1150.f, 411.f), // Soldier2 position 
        sf::Vector2f(1300.f, 411.f), // Soldier2 position 
        //sf::Vector2f(900.f, 500.f) // slime test pos
    };
    player.changePosition(738, 662);

    for (size_t i = 0; i < enemies.size(); ++i) {
        enemies[i]->changePosition(enemyPositions1a[i].x, enemyPositions1a[i].y);
    }

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices

    GameState state;
    state.loadLevel();

    // ------------------------------- TILEMAP ----------------------------------

    // ---------------------------- TESTING -----------------------------



    // ---------------------------- TESTING -----------------------------

    // ------------------------------------------ LOAD ---------------------------------
    sf::Clock GameStateClock;


    SoundFx musicState;






    //main game loop
    while (window.isOpen())
    {
        sf::Time deltaTimeTimer = GameStateClock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;
        //-------------------------------- UPDATE --------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));


        // Update enemies
        for (auto& enemy : enemies) {
            enemy->update(deltaTime, player, player.getSprite().getPosition(), state.CurrentLevel);
            enemy->attackMove(deltaTime, player);
        }
        // Update player 
        player.playerUpdate(deltaTime, enemies, mousePosition, state.CurrentLevel);
        for (auto& interactable : interactables) {
            interactable.update(deltaTime, player, enemies, state.CurrentLevel);
        }

        //cout << state.hasSpikes << endl;

        if (enemies.size() == 0) {

            if (player.getKeyState() == true) {
                state.changeTile(22, 56);
                state.changeTile(23, 57);
                state.changeTile(24, 58);
                state.changeTile(25, 53);
                state.changeTile(26, 54);
                state.changeTile(27, 55);
            }

            if (state.HasSpikes == true) {
                state.changeTile(48, 49);

                state.HasSpikes = false;
            }
            state.loadLevel();
        }



        if (enemies.size() == 0 && player.isTouchingDoor(state.CurrentLevel)) { // go to new room
            state.changeLevel(state.CurrLevelName, player, "door", musicState, enemies, interactables);
            // change keystate to false here
            // erase entire interactables vector
            interactables.erase( // Some genie code for erasing enemies from the vector
                std::remove_if( // the first parameter of erase; returns an iterator (place to begin erasing) at the dead element (enemy that is dead)
                    interactables.begin(),
                    interactables.end(),
                    [&](auto& interactable) { return true; }
                ),
                interactables.end() // the 2nd parameter; tells where to end the erasing
            );
            state.loadLevel();
        }

        if (enemies.size() == 0 && player.isTouchingStair(state.CurrentLevel)) {
            state.changeLevel(state.CurrLevelName, player, "stair", musicState, enemies, interactables);
            state.loadLevel();
        }
        player.setDamageDone(0);
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();

        window.draw(state.Map);
        for (const auto& enemy : enemies) {
            enemy->draw(window);
        }
        for (auto& interactable : interactables) {
            interactable.drawInteractable(window, state.CurrLevelName);
        }
        player.drawPlayer(window);

        for (const auto& enemy : enemies) {
            if (enemy->isDead(enemy)) {
                player.changeAmmo(20); // add ammo for every enemy killed
                cout << "Enemy killed! Your ammo is now:" << player.getAmmo() << endl;
            }
        }

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
    std::cout << "You died! " << endl;

    return 0;
}