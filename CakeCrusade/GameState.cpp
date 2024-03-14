#include "GameState.hpp"
#include <string> 
#include <algorithm>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Soldier.hpp"
#include "Enemy.hpp"
#include "Slime.hpp"
#include "Skeleton.hpp"
#include "Cutscene.hpp"
#include "RockHandler.hpp"

using namespace std;

GameState::GameState(SoundFx& s)
{ 
    LevelHeight = 14;
    LevelWidth = 23;
    tileset = "assets/tilemap/tileset1.png";
    CurrLevelName = "1a";
    hasSpikes = false;
    onMenu = true;
    isRunning = true;
    inCutscene = false;
    s.loadMusic("sound/music/andthejourneybegins.wav");
}

/*
GameState::~GameState()
{
    delete[] CurrentLevel;
}
*/

bool GameState::loadLevel() // Checks if the new level has been successfully loaded
{
    if (!Map.load(tileset, sf::Vector2u(16, 16), CurrentLevel, LevelWidth, LevelHeight)) 
        return false;
    else 
        return true;
}


void GameState::changeLevel(string levelName, Player& p, string type, SoundFx& s, vector<unique_ptr<Enemy>>& enemies) // Changes the level based on door type and current level
{
    /*---------------------------------------------- Level 1 -------------------------------------------------*/
    
    if (type == "door") {
        if (levelName == "debug") {
            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;
        }

        else if (levelName == "1a") {
            int* NewLevel = new int[23 * 14]
                {
                    18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                    18,  6,  7, 22, 23, 24,  7,  7,  7,  7,  7, 44,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                    18,  9,  0, 25, 26, 27,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  6,  7,  7,  7,  7,  7, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  0,  0, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  2,  3, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,  4,  5, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 13, 18,
                    60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;
            CurrLevelName = "1b";
            p.changePosition(1250.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(1170.f, 261.f), // Soldier1 position 
                sf::Vector2f(484.f, 586.f), // Skeleton1 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }
            


        else if (levelName == "1b") {
            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  8, 18, 18, 18, 18, 18, 18, 18, 18, 18,  6,  7,  7,  7,  7,  8, 18,
                 18,  9,   0,  0,  0,  0, 10, 18, 18, 18, 19, 20, 21, 18, 18, 18,  9,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 39,  7,  7,  7, 22, 23, 24,  7,  7,  7, 40,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "1d";
            p.changePosition(739.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(739.f, 394.f), // Soldier1 position 
                sf::Vector2f(251.f, 220.f), // Skeleton1 position 
                sf::Vector2f(1219.f, 220.f) // Skeleton2 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        /*---------------------------------------------- Level 2 -------------------------------------------------*/

        else if (levelName == "1d") { // change to 2a
            tileset = "assets/tilemap/tileset2.png"; // changes level color !! :) 

            s.loadMusic("sound/music/icycave.wav");
            
            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7,  8, 18,  6,  7,  7,  7,  7, 22, 23, 24,  7,  8, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0, 25, 26, 27,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 39,  7, 40,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 41, 12, 42,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 45, 46, 47, 12, 12, 12, 12, 13, 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2a";
            p.changePosition(291.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(293.f, 326.f), // Soldier1 position 
                sf::Vector2f(1160.f, 702.f) // Skeleton1 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        else if (levelName == "2a") { // change to 2b 

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28, 30, 28, 29, 28, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 34, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 50, 18,
                 18,  9,   2,  3,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 34, 18, 18, 50, 18,
                 18,  9,   4,  5,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 33, 18, 18, 18, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 33, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 33, 18, 18, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 34, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 34, 18, 18, 18, 18, 50, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            hasSpikes = true;

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2b";
            p.changePosition(739.f, 750.f);
            try {
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(227.f, 703.f), // Skeleton1 position 
                sf::Vector2f(227.f, 254.f) // Skeleton2 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        else if (levelName == "2b") { // change to 2d 

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0, 28, 28, 32, 28,  0,  0,  0,  0,  0,  0,  0, 28, 28, 28, 31,  0,  0, 10, 18,
                 18,  9,   0,  0, 18, 33, 18, 18,  0,  0,  0,  0,  0,  0,  0, 18, 34, 18, 18,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0, 31, 28, 28, 28,  0,  0,  0,  0,  0,  0,  0, 28, 28, 32, 28,  0,  0, 10, 18,
                 18,  9,   0,  0, 18, 18, 34, 18,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 33,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2d";
            p.changePosition(739.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.13f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(738.f, 253.f), // Soldier1 position - make bigger soldier 
                sf::Vector2f(1246.f, 222.f), // Skeleton1 position
                sf::Vector2f(228.f, 222.f), // Skeleton2 position
                sf::Vector2f(738.f, 475.f) // Slime1 position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

            /*---------------------------------------------- Level 3 -------------------------------------------------*/

        else if (levelName == "2d") { // change to 3a
            tileset = "assets/tilemap/tileset3.png"; // changes level color !! :)

            s.loadMusic("sound/music/MysteriousDungeon.wav");

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  8, 18, 18, 18, 18, 18, 18, 18, 18, 18,  6,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0, 10, 18, 18, 18, 18, 18, 18, 18, 18, 18,  9,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 10, 18, 18, 18, 18, 18, 18, 18, 18, 18,  9,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 10, 18, 18, 18, 19, 20, 21, 18, 18, 18,  9,  0,  0,  0,  0, 10, 18,
                 18,  9, 28, 31, 28, 30, 37,  7,  7,  7, 22, 23, 24,  7,  7,  7, 38, 28, 30, 28, 29, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "3a";
            p.changePosition(739.f, 750.f);
            try {
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl; 
            }
            vector<sf::Vector2f> enemyPositions1b = { // CHANGE THESE POSITIONS WHEN U CAN GET THEM 
                sf::Vector2f(258.f, 250.f), // Skeleton1 position 
                sf::Vector2f(1218.f, 250.f) // Skeleton2 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }

        }

        else if (levelName == "3a") { // changes to 3b

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18,
                 18,  6,  7,  7,  7,  8,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  8, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0, 25, 26, 27,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10, 11, 12, 17,  0,  0, 16, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 18,  9,  0,  0,  0, 10, 18, 18,  9,  0,  0, 10, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  9,  0,  0,  0, 39,  7,  7, 40,  0,  0, 39,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  2,  3, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0,  4,  5, 10, 18,
                 18, 11, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            hasSpikes = true;

            CurrLevelName = "3b";
            p.changePosition(226.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 0.5f));
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(227.f, 248.f), // Soldier1 position - make bigger soldier 
                sf::Vector2f(643.f, 248.f), // Soldier2 position
                sf::Vector2f(1187.f, 285.f) // Skeleton1 position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }

        }

        else if (levelName == "2b") {

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0, 28, 28, 32, 28,  0,  0,  0,  0,  0,  0,  0, 28, 28, 28, 31,  0,  0, 10, 18,
                 18,  9,  0,  0, 18, 33, 18, 18,  0,  0,  0,  0,  0,  0,  0, 18, 34, 18, 18,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0, 31, 28, 28, 28,  0,  0,  0,  0,  0,  0,  0, 28, 28, 32, 28,  0,  0, 10, 18,
                 18,  9,  0,  0, 18, 18, 34, 18,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 33,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2d";
            p.changePosition(739.f, 750.f);

        }

        else if (levelName == "3b") { // changes to 3d

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9, 48, 48, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 48, 48, 10, 18,
                 18,  9, 48, 48, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 48, 48, 10, 18,
                 18,  9, 48, 48, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 48, 48, 10, 18,
                 18,  9, 48, 48, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 48, 48, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "3d";
            p.changePosition(739.f, 750.f);

            hasSpikes = true;
            try {
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = { 
                sf::Vector2f(450.f, 248.f), // Skeleton1 position
                sf::Vector2f(1026.f, 248.f) // Skeleton2 position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }

        }

        /*---------------------------------------------- Level 4 -------------------------------------------------*/

        else if (levelName == "3d") { // changes to 4a

            tileset = "assets/tilemap/tileset4.png"; // changes level color !! :)

            s.loadMusic("sound/music/ExploringTheUnknown.wav");

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7, 22, 23, 24,  7,  8,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0, 25, 26, 27,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 41, 42,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0, 39, 40,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 11, 12, 45, 46, 47, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "4a";
            p.changePosition(1185.f, 750.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 0.5f));
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f));
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.20f));

                enemies.push_back(make_unique<RockHandler>(350.f, 30.f, 30.f, 0.2f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(1184.f, 220.f), // Knight1 position
                sf::Vector2f(640.f, 220.f), // Knight2 position
                sf::Vector2f(417.f, 696.f), // Slime1 position
                sf::Vector2f(700.f, 350.0f) // Rock position

            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }

        }

        else if (levelName == "4a") { // change to 4b

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9, 25, 26, 27,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48, 28, 28, 32, 28, 28, 28, 28, 28, 31, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48, 34, 18, 18, 18, 18, 18, 33, 18, 18, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48, 18, 33, 18, 18, 34, 18, 18, 18, 18, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0, 48, 18, 18, 18, 18, 18, 18, 18, 33, 18, 48,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "4b";
            p.changePosition(739.f, 750.f);

            hasSpikes = true;
            try {
                
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 0.5f)); 
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f));
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f));
                enemies.push_back(make_unique<RockHandler>(350.f, 30.f, 30.f, 0.2f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(1217.f, 381.f), // Knight1 position
                sf::Vector2f(224.f, 316.f), // Knight2 position
                sf::Vector2f(739.f, 250.f), // Skeleton1 position
                sf::Vector2f(700.f, 350.0f) // Rock position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        else if (levelName == "4b") { // change to 4c
            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0, 48,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9, 48, 48, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0, 28, 28, 32, 28, 31, 28, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0, 18, 33, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0, 34, 18, 18, 34, 18, 18, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 33, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 48, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "4c";
            p.changePosition(739.f, 750.f);

            hasSpikes = true;
            try {
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); // Knight1
                enemies.push_back(make_unique<Skeleton>(150.f, 20.f, 20.f, 0.0f)); // Knight2
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.12f)); // Slime1
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.14f)); // Slime2
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.15f, 0.5f)); // Skeleton1
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // Skeleton2
                enemies.push_back(make_unique<RockHandler>(350.f, 30.f, 30.f, 0.2f)); // Rocks
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(1282.f, 733.f),// Skeleton1 position
                sf::Vector2f(194.f, 220.f), // Skeleton2 position
                sf::Vector2f(256.f, 665.f), // Slime1 position
                sf::Vector2f(1188.f, 251.f), // Slime2 position
                sf::Vector2f(611.f, 189.f), // Knight1 position
                sf::Vector2f(866.f, 189.f), // Knight2 position
                sf::Vector2f(700.f, 350.0f) // Rock position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        /*---------------------------------------------- BOSS TIME -------------------------------------------------*/

        else if (levelName == "4c") { // change to 5a (pre-boss room)

            tileset = "assets/tilemap/tileset5.png"; // changes level color !! :)

            s.music.stop();

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,   6,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  50, 28, 30, 28, 29, 28,  0,  0,  0, 25, 26, 27,  0,  0,  0, 28, 30, 28, 29, 28, 50, 18,
                 18,  50, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 34, 18, 50, 18,
                 18,  50, 34, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 34, 50, 18,
                 18,  50, 18, 33, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 50, 18,
                 18,  50, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 34, 18, 18, 50, 18,
                 18,  50, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 33, 18, 18, 18, 18, 50, 18,
                 18,  50, 18, 18, 33, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 33, 50, 18,
                 18,  50, 18, 18, 18, 34, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 33, 18, 18, 18, 50, 18,
                 18,  50, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 34, 18, 50, 18,
                 18,  50, 18, 34, 18, 18, 18,  0,  0,  0,  0,  0,  0,  0,  0,  0, 34, 18, 18, 18, 18, 50, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "5a";
            p.changePosition(739.f, 750.f);

        }

        else if (levelName == "5a") { // change to 5b (boss room)

            s.loadMusic("sound/music/DecisiveBattle.wav");

            int* NewLevel = new int[23 * 14]
            {
                18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                18,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "5b";
            p.changePosition(739.f, 750.f);
            
        }




    }


    /*---------------------------------------------- Stairs -------------------------------------------------*/


    else if (type == "stair") {

        if (levelName == "1b") {
            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   4,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0, 28, 28, 32, 28, 31, 28, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0, 18, 33, 18, 18, 18, 18, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0, 34, 18, 18, 34, 18, 18, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 33, 18,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "1c";
            p.changePosition(290.f, 180.f);
            try {
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.17f, 0.5f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Soldier>(200.f, 50.f, 50.f, 0.13f, 0.5f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(258.f, 687.f), // Soldier1 position 
                sf::Vector2f(1220.f, 243.f) // Soldier2 position
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        else if (levelName == "1c") {
            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7, 22, 23, 24,  7,  7,  7,  7,  7, 44,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0, 25, 26, 27,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  6,   7,  7,  7,  7,  7, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   2,  3, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   4,  5, 43,  0,  0,  0,  0,  0,  0, 43,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "1b";
            p.changePosition(193.f, 616.f);
        }

        /*---------------------------------------------- Level 2 -------------------------------------------------*/

        else if (levelName == "2c") { // go back to 2b

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28, 30, 28, 29, 28, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 34, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 18, 50, 18,
                 18,  9,   2,  3,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 34, 18, 18, 50, 18,
                 18,  9,   4,  5,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 33, 18, 18, 18, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 18, 33, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 33, 18, 18, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18, 18, 18, 34, 18, 50, 18,
                 18,  9,   0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0,  0,  0,  0, 34, 18, 18, 18, 18, 50, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2b";
            p.changePosition(284.f, 456.f);

        }

        else if (levelName == "2b") { // change to 2c

            int* NewLevel = new int[23 * 14]
            {
                 18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,   7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  3, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  5, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,   0,  0,  0,  0, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            hasSpikes = true; 

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "2c";
            p.changePosition(1187.f, 456.f);
            try {
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.20f)); // give diff speeds to avoid complete overlapping
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(544.f, 471.f) // Slime1 position 
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }


        /*---------------------------------------------- Level 3 -------------------------------------------------*/


        else if (levelName == "3c") {

            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18,
                 18,  6,  7,  7,  7,  8,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  8, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0, 25, 26, 27,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10,  9,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0, 10, 11, 12, 17,  0,  0, 16, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 18,  9,  0,  0,  0, 10, 18, 18,  9,  0,  0, 10, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  9,  0,  0,  0, 39,  7,  7, 40,  0,  0, 39,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  2,  3, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 49,  0,  0,  0,  0,  4,  5, 10, 18,
                 18, 11, 45, 46, 47, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "3b";
            p.changePosition(1282.f, 627.f);

        }

        else if (levelName == "3b") { // changes to 3c

            int* NewLevel = new int[23 * 14]
            {
                    18,  18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                    18,  6,   7,  7,  8, 18,  6,  7,  7,  7,  7,  7,  7,  7,  8, 18,  6,  7,  7,  7,  7,  8, 18,
                    18,  9,   2,  3, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   4,  5, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 10, 18,  9,  0,  0, 41, 12, 42,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0, 10, 18,  9,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0, 14,  7, 15,  0,  0, 10, 18,  9,  0,  0, 14,  7, 15,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  9,   0,  0,  0,  0,  0,  0,  0, 10, 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                    18,  11, 12, 12, 12, 12, 12, 12, 12, 13, 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                    60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            hasSpikes = true;

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;

            CurrLevelName = "3c";
            p.changePosition(193.f, 311.f);
            try {
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.035f)); // give diff speeds to avoid complete overlapping
                enemies.push_back(make_unique<Slime>(300.f, 10.f, 5.f, 0.020f));
            }
            catch (const bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            }
            vector<sf::Vector2f> enemyPositions1b = {
                sf::Vector2f(353.f, 733.f), // Slime1 position 
                sf::Vector2f(995.f, 733.f)
            };
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i]->changePosition(enemyPositions1b[i].x, enemyPositions1b[i].y);
            }
            for (auto& enemy : enemies) {
                enemy->initialize();
                enemy->load();
            }
        }

        /*---------------------------------------------- Level 4 -------------------------------------------------*/

        else if (levelName == "debug") {
            int* NewLevel = new int[23 * 14]
            {
                 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
                 18,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
                 18, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 18,
                 60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
            };

            std::copy(NewLevel, NewLevel + (23 * 14), CurrentLevel);

            delete[] NewLevel;
        }














    }

}

void GameState::changeTile(int currTile, int newTile)
{
    for (int i = 0; i < 322; i++) {
        if (CurrentLevel[i] == currTile) {
            CurrentLevel[i] = newTile;
        }
    }
}

// False positives
#pragma warning(push)
#pragma warning(disable:6385)
#pragma warning(disable:6386)

void GameState::drawHearts(Player& p) // 
{
    for (int i = 0; i < p.HeartContainerCount; i++) { // Draw every full heart needed
        CurrentLevel[i] = 67; // 67 is the full tile
    }

    if (p.HalfHeartCount / 2 != p.HeartContainerCount) { // If damage has been taken
        int counter = 1; // counter represents the current heart

        for (int i = (p.HeartContainerCount * 2) - p.HalfHeartCount; i > 0; i) { // i = every half heart lost

            if (CurrentLevel[int(p.HeartContainerCount) - counter] != 65) { // If the current heart isnt empty
                if (CurrentLevel[int(p.HeartContainerCount) - counter] == 67) { // If the current heart is full, make it half
                    CurrentLevel[int(p.HeartContainerCount) - counter] = 66;
                    i--; // one less half heart to create

                    if (i >= 1) { // if we need to change the half heart sprite -> empty
                        CurrentLevel[int(p.HeartContainerCount) - counter] = 65;
                        i--; // one less half heart to create
                    }

                    counter++; // we have finished modifying the current heart, move to the next

                }
            }
        }
    }

    for (int i = 0; i < p.GoldHeartContainerCount; i++) { // Draw enemy gold hearts as needed
        CurrentLevel[i + int(p.HeartContainerCount)] = 69;
    }

    if (p.GoldHalfHeartCount / 2 != p.GoldHeartContainerCount) { // If damage has been taken
        int counter = 1; // counter represents current heart
        int offset = int(p.HeartContainerCount + p.GoldHeartContainerCount); // Gold heart offset, as they are drawn after red heart containers

        for (int i = int(p.GoldHeartContainerCount * 2 - p.GoldHalfHeartCount); i > 0; i) { // i = every half heart lost

            if (CurrentLevel[offset - counter] != 18) { // if gold container exists
                if (CurrentLevel[offset - counter] == 69) { // if full heart, make half
                    CurrentLevel[offset - counter] = 68;
                    i--; // one less heart to draw

                    if (i >= 1) { // if half hearts are leftover
                        CurrentLevel[offset - counter] = 18; // if half heart, make empty
                        i--;
                    }

                    counter++; // move to next heart

                }
            }
        }
    }

}

#pragma warning(pop)
