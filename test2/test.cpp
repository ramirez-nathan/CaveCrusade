#include "pch.h"


/*TEST(ArrowTest, checkforTextureLoad) {
    sf::Texture texture;
    texture.loadFromFile("assets/player/textures/new_arrow.png");
    EXPECT_TRUE(texture.getSize().x > 0);
    EXPECT_TRUE(texture.getSize().y > 0);
}*/

TEST(SimpleTest, testing) {
    EXPECT_TRUE(2, 2, 4);
}

/*TEST(EntityTest, ChangeHealth) {
    mockEntity entity(60,100, 10, 5); // Creating an instance of the Entity class
    float initialHealth = entity.getHealth();    

    // Change the health by a certain amount
    float healthChange = -20; // Decreasing health
    entity.changeHealth(healthChange);

    // Check if the health has changed correctly
    float expectedHealth = initialHealth + healthChange;
    EXPECT_FLOAT_EQ(entity.getHealth(), expectedHealth);
}*/
