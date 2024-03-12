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
	vector<Arrow> SkellyArrows;
	const string SkeletonArrowPath = "assets/enemies/skelly/attacking/arrow.png";
	float MaxFireRate;
	double FireRateTimer;
	sf::Texture AttackTexture;

	sf::Clock AttackClock;

	bool ShootingArrow = false;
	bool ShootingAnimationComplete = true;
	bool FinishedBowAnimation = false;

	int SkeletonDirection;

public:
	Skeleton(float h,float dmg,float def,float spd);
	~Skeleton() = default;
	virtual void load() override;
	void handleSkeletonMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls);
	void handleArrow(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	virtual void update(const double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual void attackAnimation(const sf::Vector2f& playerPosition) override;
	bool isKnockbackEnabled() const override {return false;} // Skeletons do not get knocked back
};