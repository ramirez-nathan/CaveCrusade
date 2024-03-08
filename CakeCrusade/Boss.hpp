#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Math.hpp"
#include "Enemy.hpp"

//things i want the boss to be able to do:
	//be able to go transparent
	//be able to jump to a "random" location on the map

class Boss : public Enemy
{
public:
	Boss(float h, float dmg, float def, float spd);
	~Boss() = default;
	virtual void initialize() override;
	void load();
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;
	void handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void transparency(double deltaTime);
};

