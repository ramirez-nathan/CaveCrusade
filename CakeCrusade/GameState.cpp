#include "GameState.hpp"
#include <string> 

using namespace std;


GameState::GameState()
{ 
    LevelHeight = 11;
    LevelWidth = 22;
}

bool GameState::loadLevel()
{
    if (!Map.load("assets/tilemap/tileset.png", sf::Vector2u(16, 16), CurrentLevel, LevelWidth, LevelHeight)) 
        return false;
    else 
        return true;
}

void GameState::changeLevel(string levelName)
{
}


