#include "TileMap.hpp"
#include <string>
#include "Player.hpp"
#include "SoundFx.hpp"

using namespace std;

class GameState {
public:
    GameState();

    bool loadLevel();
    void changeLevel(string levelName, Player& p, string type, SoundFx& s, vector<unique_ptr<Enemy>>& enemies);
    bool hasSpikes;
    string tileset;
    string CurrLevelName;
    void changeTile(int currTile, int newTile);

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
        60, 62, 18, 59, 63, 18, 61, 64, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    };


private:
    unsigned int LevelWidth;
    unsigned int LevelHeight;

};
