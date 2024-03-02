#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Math.hpp"

using namespace std;

class Slime : public Entity
{
public:
	Slime(float h, float dmg, float def, float spd);
	~Slime() = default;
	
	virtual void initialize() override;
	virtual void load() override;
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;
	virtual void attackMove() override;
};