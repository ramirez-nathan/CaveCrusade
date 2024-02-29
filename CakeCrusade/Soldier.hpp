#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Math.hpp"

using namespace std;

class Soldier : public Entity
{
private:
	sf::Vector2f Direction;


	int SpriteX = 0;
	int SpriteY = 0;

	float SoldierSpeed;

public:
	Soldier(float h, float dmg, float def);
	~Soldier();


	void initialize();
	void load();
	void update(double deltaTime, const sf::Vector2f& target, int level[]);
	void drawSoldier(sf::RenderWindow& window);
	virtual void attackMove() override;

};