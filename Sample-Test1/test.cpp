#include "pch.h"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Player.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Arrow.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Enemy.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Entity.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Math.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Skeleton.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Soldier.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Slime.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Knight.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Interactable.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\Rock.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\RockHandler.cpp"
#include "C:\Users\amana\source\repos\final-project-amana032-rlee205-rly014-nrami112\CakeCrusade\SoundFx.cpp"

// Player Tests
TEST(PlayerTest, checkForLoad) { 
    EXPECT_NO_THROW(
        Player player(300.0, 300.0, 300.0, 300.0);
        player.load();
    );
}

TEST(PlayerTest, checkGoldHeartDeclaration) { 
    Player player(300.0, 300.0, 300.0, 300.0);
    player.load();

    EXPECT_EQ(player.getGoldHalfHearts(), 0);
    EXPECT_EQ(player.getGoldHeartContainer(), 2);

}

TEST(PlayerTest, checkHeartDeclaration) {
    Player player(300.0, 300.0, 300.0, 300.0);
    player.load();

    EXPECT_EQ(player.getHalfHearts(), 8);
    EXPECT_EQ(player.getHeartContainer(), 4);

}

// Arrow Tests
TEST(ArrowTest, checkforTextureLoad) {
    Arrow arrow;

    sf::Texture& texture = arrow.getArrowTexture("bad/file/path");
    EXPECT_FALSE(texture.getSize().x > 0);
    EXPECT_FALSE(texture.getSize().y > 0);
}


::testing::AssertionResult IsBetweenRange(int val, int lowBound, int highBound) {
    if ((val >= lowBound) && (val <= highBound))
        return::testing::AssertionSuccess();
    else
        testing::AssertionFailure()
        << val << " is outside the bounds of the map which are from " << lowBound << " to " << highBound;
}

// TileMap Tests
TEST(TileMapTests, playerOnTheMap) {
    Player player(300.0, 300.0, 300.0, 300.0);
    sf::Vector2f playerPosition = player.getSprite().getPosition();
    EXPECT_TRUE((playerPosition.x >= 0 && playerPosition.x <= 1472) &&
        (playerPosition.y >= 0 && playerPosition.y <= 896));
}

// Enemy Tests
TEST(EnemyTests, updateLocationSkelly) {
    Skeleton skeleton(200.0, 30.5, 20.0, 29.5);
    Player player(100.0, 30.0, 50.0, 20.0);
    const sf::Vector2f targetPosition(30.5f, 40.5f);

    EXPECT_GT(targetPosition.x, 0);
}

TEST(EnemyTests, updateLocationSoldier) {
    Soldier soldier(200.f, 50.f, 50.f, 0.17f, 0.5f);
    Player player(100.0, 30.0, 50.0, 20.0);
    const sf::Vector2f targetPosition(30.5f, 40.5f);

    EXPECT_GT(targetPosition.x, 0);
}

TEST(EnemyTests, updateLocationSlime) {
    Slime slime(200.0, 30.5, 20.0, 29.5);
    Player player(100.0, 30.0, 50.0, 20.0);
    const sf::Vector2f targetPosition(30.5f, 40.5f);

    EXPECT_GT(targetPosition.x, 0);
}

TEST(EnemyTests, updateLocationKnight) {
    Knight knight(200.f, 50.f, 50.f, 0.17f, 0.5f);
    Player player(100.0, 30.0, 50.0, 20.0);
    const sf::Vector2f targetPosition(30.5f, 40.5f);

    EXPECT_GT(targetPosition.x, 0);
}

// Sound Tests
TEST(SoundTest, checkForLoad) {
    EXPECT_NO_THROW(
        SoundFx music;
    );
}

TEST(SoundTest, checkBadTitle) {
    SoundFx music;
    bool load = music.loadMusic("bad/title");
    EXPECT_FALSE(load);
}

// Interactable Tests
TEST(InteractableTest, checkForLoad) {
    EXPECT_NO_THROW(
        Interactable chest("Chest");
        
    );
}

TEST(InteractableTest, checkForChest) {
    Interactable chest("Chest");
    bool b = chest.isTouched();

    EXPECT_FALSE(b);
}

// Rock Tests
TEST(RockTest, checkForLoad) {
    EXPECT_NO_THROW(
        Rock r;
    );
}

TEST(RockTest, checkForFalling) {
    Rock r;
    sf::Vector2f initPos = r.getRockPosition(); 
    r.initialize(initPos, initPos, 0.3f);
    r.update(2.5);
    sf::Vector2f newPos = r.getRockPosition(); 

    EXPECT_GT(newPos.y, initPos.y);
}