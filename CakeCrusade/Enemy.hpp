#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

class Enemy : public Entity {
public:
	Enemy(float h, float dmg, float def);
	virtual void attackMove() override;
	bool canAttack(const sf::Vector2f& playerPosition, float attackRange) const;
	void getKnockedBack();
	void target();
	virtual ~Enemy() = default;
};