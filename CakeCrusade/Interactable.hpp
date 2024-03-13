#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Math.hpp"
#include <vector>
#include <ostream>
#include <memory>
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "GameState.hpp"

using namespace std;

class Interactable
{
protected:
	string ItemName = "";
	string TexturePath = "";

	bool IsTouched = false;
	bool ReadyToSpawn = false;
	bool IdleAnimationComplete = true;


	sf::Clock ChestClock;
	bool ChestIsOpened = false;
	bool ChestAnimationComplete = true;
	bool IsFinished = false;

	sf::Sprite Sprite;
	sf::Texture Texture;
	sf::Vector2i Size;

	int SpriteX = 0;
	int SpriteY = 0;

	int ChestSpriteX = -1;


	sf::RectangleShape BoundingRectangle;
	
	vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46, 47, 48 };

public:
	Interactable(string name);

	~Interactable() = default;
	
	void initialize();
	void load();
	void update(const double deltaTime, Player& player, vector<unique_ptr<Enemy>>& enemies, int level[]);


	void chestAnimation();

	void drawInteractable(sf::RenderWindow& window, string currLevelName);

	bool isTouched();

	int getSizeX() const { return Size.x; }
	int getSizeY() const { return Size.y; }

	sf::Sprite& getSprite() { return Sprite; }
	sf::RectangleShape& getHitBox() { return BoundingRectangle; }

	void changePosition(float x, float y) { Sprite.setPosition(sf::Vector2f(x, y)); }
		
};

#endif
