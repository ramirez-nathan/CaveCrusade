#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"

class Skeleton : public Entity
{
public:
	Skeleton(float h,float dmg,float def,float spd);
	~Skeleton() = default;
	virtual void attackMove() override;
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;
};