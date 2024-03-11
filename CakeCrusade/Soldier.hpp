#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Math.hpp"
#include "Enemy.hpp"

using namespace std;

class Soldier : public Enemy
{
private:
	float meleeRange;
	const float aggressiveRange = 350.0f;
	float attackCooldown = 20.0f;
	sf::Clock attackClock;
	sf::Texture attackTexture;
	/*int SwingingSpriteX = 1;
	int SwingingSpriteY = 0;
	int WalkingSpriteX = 0;
	int WalkingSpriteY = 0;*/


public:
	Soldier(float h, float dmg, float def, float spd, float rng);
	~Soldier() = default;
	virtual void attackMove(const double deltaTime, Entity& player) override;
	virtual void load() override;
	bool canAttack(const sf::Vector2f& playerPosition) const;
	bool isAgressive(const sf::Vector2f& playerPosition) const;
	void makeAggressive(const sf::Vector2f& playerPosition);
	virtual void attackAnimation(const sf::Vector2f& playerPosition) override;
	virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) override;

};