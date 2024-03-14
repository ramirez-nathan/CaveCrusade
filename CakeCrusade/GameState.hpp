#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include "TileMap.hpp"
#include <string>
#include "Player.hpp"
#include "SoundFx.hpp"


using namespace std;

class Interactable;

class GameState {
public:
    GameState(SoundFx& s);
    ~GameState() = default;

    bool loadLevel();
    void changeLevel(string levelName, Player& p, string type, SoundFx& s, vector<unique_ptr<Enemy>>& enemies, vector<Interactable>& interactables);

    bool HasSpikes;
    bool OneCDone = false;
    bool TwoCDone = false;
    bool ThreeCDone = false;

    bool OneCChestOpened = false;
    bool TwoCChestOpened = false;
    bool ThreeCChestOpened = false;

    bool PlayerHasKey = true;

    bool ItemsReadyToSpawn = false;
    bool ChestIsOpened = false;

    string Tileset;
    bool onMenu;
    bool isRunning;
    bool inCutscene;

    string tileset;
    string CurrLevelName;
    void changeTile(int currTile, int newTile);

    void drawHearts(Player& p);

    TileMap Map;

    

    int CurrentLevel[23 * 14] =
    {
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18,  6,  7,  7,  7,  7,  7,  7,  7,  7, 22, 23, 24,  7,  7,  7,  7,  7,  7,  7,  7,  8, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0, 25, 26, 27,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 18,
        18,  9,  0,  0,  0,  0, 41, 12, 12, 12, 12, 12, 12, 12, 12, 12, 42,  0,  0,  0,  0, 10, 18,
        18, 11, 12, 12, 12, 12, 13, 18, 18, 18, 18, 18, 18, 18, 18, 18, 11, 12, 12, 12, 12, 13, 18,
        60, 62, 18, 59, 63, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    };


private:
    unsigned int LevelWidth;
    unsigned int LevelHeight;

};
#endif
