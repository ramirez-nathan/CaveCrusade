#include "pch.h"

//check for loading of texture, bounds of hitbox, 


/*TEST(ArrowTest, checkforTextureLoad) {
    Arrow arrow;
    sf::Texture& texture = arrow.getArrowTexture();
    EXPECT_TRUE(texture.getSize().x > 0);
    EXPECT_TRUE(texture.getSize().y > 0);
}*/


TEST(PlayerTests, checkforTextureLoad) {
    Player player(300.0, 300.0, 300.0, 300.0);
    player.load();
    EXPECT_TRUE(player.getSizeX(), 49);
}

class mockEntity :public Entity {
public:
    //MOCK_METHOD(void, attackMove, (), (override));
};

/*TEST(EntityTest, changeHealth) {
    Entity entity(60,100, 10, 5); // Creating an instance of the Entity class
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

TEST(TileMapTests, OnTheMap) {
    int tileMapValue = 6;
    EXPECT_TRUE(IsBetweenRange(tileMapValue, 0, 12));
    int tileMapValue2 = 15;
    EXPECT_FALSE(IsBetweenRange(tileMapValue2, 0, 12));
}

TEST(SkeletonTests, arr) {
    Skeleton skeleton(20.5, 30.4, 20.4, 29.9);
    EXPECT_LE();
}



/*TEST(SimpleTest, testing) {
    EXPECT_TRUE(2, 2, 4);
}*/

