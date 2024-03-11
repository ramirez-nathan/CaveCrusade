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
	float attackCooldown = 0.20f;
	sf::Clock attackClock;
	sf::Texture attackTexture;

public:
	Soldier(float h, float dmg, float def, float spd, float rng);
	~Soldier() = default;
	virtual void attackMove(const double deltaTime, Entity& player) override;
	virtual void load() override;
	bool canAttack(const sf::Vector2f& playerPosition) const;
	virtual void attackAnimation(const sf::Vector2f& playerPosition) override;


};