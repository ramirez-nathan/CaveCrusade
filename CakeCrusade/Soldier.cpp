#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def, float spd) 
	: Entity(h, dmg, def, spd)
{
}

void Soldier::attackMove() {
    // Implement how the enemy attacks
}