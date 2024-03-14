#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

class Enemy : public Entity {
protected:
	
	sf::Clock EnemyIdleClock;
	const float MaxAttackRate = 1000.f;
	float AttackTimer = 0.0f;
	
public:
	Enemy(float h, float dmg, float def, float spd);
	virtual void attackMove(const double deltaTime, Entity& player) override;
	bool canAttack(const sf::Vector2f& playerPosition, float attackRange) const;
	virtual void attackAnimation(const sf::Vector2f& playerPosition);
	virtual bool isDead(const unique_ptr<Enemy>& entity);
	virtual ~Enemy() = default;
	virtual bool isKnockbackEnabled() const { return true;}
		
};