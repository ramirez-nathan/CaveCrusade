#include "pch.h"
#include <SFML/Graphics.hpp>
#include "C:\\Users\\User\\source\\repos\\CS100 Final Project\\CakeCrusade\\Entity.hpp"
#include "C:\\Users\\User\\source\\repos\\CS100 Final Project\\CakeCrusade\\Player.hpp"
#include "C:\\Users\\User\\source\\repos\\CS100 Final Project\\CakeCrusade\\Arrow.hpp"
#include "C:\\Users\\User\\source\\repos\\CS100 Final Project\\CakeCrusade\\TileMap.hpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(PlayerTests, checkforTextureLoad) {
    Player player(300.0, 300.0, 300.0, 300.0);
    player.load();
    EXPECT_TRUE(player.getSizeX(), 49);
}