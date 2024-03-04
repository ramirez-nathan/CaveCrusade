#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"

using namespace std;

class Skeleton : public Enemy
{
private:
	vector<Arrow> Arrows;

	float MaxFireRate;
	double FireRateTimer;

public:
	Skeleton(float h,float dmg,float def,float spd);
	~Skeleton() = default;
	virtual void load() override;
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;
	void handleArrow(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	virtual void update(const double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) override;
	virtual void draw(sf::RenderWindow& window) override;
};