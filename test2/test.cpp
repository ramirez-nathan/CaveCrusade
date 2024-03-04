#include "pch.h"


TEST(EntityTest, ChangeHealth) {
    Entity entity(100, 10, 5); // Creating an instance of the Entity class
    float initialHealth = entity.getHealth();

    // Change the health by a certain amount
    float healthChange = -20; // Decreasing health
    entity.ChangeHealth(healthChange);

    // Check if the health has changed correctly
    float expectedHealth = initialHealth + healthChange;
    EXPECT_FLOAT_EQ(entity.getHealth(), expectedHealth);
}
