#pragma once

#include "Soldier.hpp"

using namespace std;

class Knight : public Soldier {
private:
	float MaxSwingRate;
	double SwingRateTimer;


public: 
	Knight(float h, float dmg, float def, float spd, float rng);
	~Knight() = default;
	virtual void attackMove(const double deltaTime, Entity& player) override { };
	virtual void load() override;
	bool canAttack(const sf::Vector2f& playerPosition);
	virtual void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) override;

    virtual void handleSword(const double deltaTime, Entity& player, sf::Vector2f& mousePosition, int level[], vector<int>& walls) override;

	void swingingAnimation();
	bool isAggressive(const sf::Vector2f& playerPosition) const;
	void makeAggressive(const sf::Vector2f& playerPosition);


};