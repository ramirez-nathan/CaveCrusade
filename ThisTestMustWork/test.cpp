#include "pch.h"
#include "../dependencies/SFML/include/SFML/System/Vector2.hpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ArrowTest, checkforTextureLoad) {
    Arrow arrow;
    sf::Texture& texture = arrow.getArrowTexture();
    EXPECT_TRUE(texture.getSize().x > 0);
    EXPECT_TRUE(texture.getSize().y > 0);
}

TEST(PlayerTests, checkforTextureLoad) {
    Player player(300.0, 300.0, 300.0, 300.0);
    player.load();
    EXPECT_TRUE(player.getSizeX(), 49);
}


/*class mockEntity :public Entity {
public:
    MOCK_METHOD(mockEntity, mockEntity, (float h, float dmg, float def, float spd));
    MOCK_METHOD(void, update, (double deltaTime, Entity& player, const sf::Vector2f& target, int level[]), (override));
}

TEST(EntityTest, changeHealth) {
    mockEntity entity;
    float initialHealth = entity.getHealth();

    // Change the health by a certain amount
    float healthChange = -20; // Decreasing health
    entity.changeHealth(healthChange);

    // Check if the health has changed correctly
    float expectedHealth = initialHealth + healthChange;
    EXPECT_FLOAT_EQ(entity.getHealth(), expectedHealth);
}*/


::testing::AssertionResult IsBetweenRange(int val, int lowBound, int highBound) {
    if ((val >= lowBound) && (val <= highBound))
        return::testing::AssertionSuccess();
    else
        testing::AssertionFailure()
        << val << " is outside the bounds of the map which are from " << lowBound << " to " << highBound;
}

TEST(TileMapTests, tileOnTheMap) {
    int tileMapValue = 7;
    EXPECT_TRUE(IsBetweenRange(tileMapValue, 0, 12));
    int tileMapValue2 = 80;
    EXPECT_FALSE(IsBetweenRange(tileMapValue2, 0, 63));
}

TEST(TileMapTests, playerOnTheMap) {
    Player player(300.0, 300.0, 300.0, 300.0);
    sf::Vector2f playerPosition();
    EXPECT_DEATH(playerPosition, "Player collided with the wall!");
}

/*TEST(SkeletonTests, updateLocation) {
    Skeleton skeleton(200.0, 30.5, 20.0, 29.5);
    Entity player(100.0, 30.0, 50.0, 20.0);
    const sf::Vector2f targetPosition(30.5f, 40.5f);

    EXPECT_GT(player,0);
}*/
