#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def, float spd, float rng)
	: Enemy(h, dmg, def, spd), meleeRange(rng)
{
}

void Soldier::load()
{
	loadTexture("assets/enemies/evil_soldier/textures/evil_soldier_idle.png");
	Entity::load();
}

void Soldier::attackMove(const double deltaTime, Entity& player) 
{

}

