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
	//float MeleeRange;
	float AttackCooldown = 1.0f;

	float MaxSwingRate;
	double SwingRateTimer;


	sf::Texture WalkingTexture;
	sf::Texture AttackTexture;

	sf::Clock AttackClock;
	sf::Clock WalkClock;
	
	bool IsAttacking = false;
	bool AttackingAnimationComplete = true;
	bool FinishedAttackingAnimation = false;

public:
	Soldier(float h, float dmg, float def, float spd, float rng);
	~Soldier() = default;
	virtual void attackMove(const double deltaTime, Entity& player) override;
	virtual void load() override;
	bool canAttack(const sf::Vector2f& playerPosition) const;
	virtual void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) override;

	void handleSword(const double deltaTime, Entity& player, sf::Vector2f& mousePosition, int level[], vector<int>& walls);
	
	void swingingAnimation();
};