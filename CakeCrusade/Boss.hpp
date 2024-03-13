#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rock.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"

using namespace std;

class Boss : public Enemy
{
private: 
	vector<Rock> Rocks;
	float maxFireRate;
	double fireRateTimer;
public:
	Boss(float h, float dmg, float def, float spd);
	~Boss() = default;
	virtual void initialize() override;
	virtual void load() override;
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;
	void handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void transparency(double deltaTime);
	void handleBat(const double deltaTime, Entity& player, const sf::Vector2f& target, double& speedRateTimer, const float& maxSpeed, int level[], vector<int>& walls);
	virtual void draw(sf::RenderWindow& window) override;
	void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]);
};

