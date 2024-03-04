#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Math.hpp"
#include "Enemy.hpp"

using namespace std;

class Soldier : public Enemy
{
public:
	Soldier(float h, float dmg, float def, float spd);
	~Soldier() = default;
	//virtual void attackMove(const double deltaTime, Entity& player) override;
	virtual void load() override;


};