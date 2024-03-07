#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "memory"

using namespace std;

class Player : public Entity
{
private:
	vector<Arrow> Arrows;

	float MaxFireRate;
	double FireRateTimer;

	int SpriteX = 0;
	int SpriteY = 0;
	int ArrowSpriteX = 0;
	int ArrowSpriteY = 0;
	float timer = 0.0f;
public:
	Player(float h, float dmg, float def, float spd);
	~Player();

	void initialize() override;
	void load() override; 
	// void arrowShootAnimation(const double deltaTime, sf::Vector2f& direction); // WIP
	bool isTouchingDoor(int level[]);
	void playerUpdate(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int level[]);
	void drawPlayer(sf::RenderWindow& window);
	virtual void attackMove(const double deltaTime, Entity& enemy) override;
	void handleArrow(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void handleMovement(const double deltaTime, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
};