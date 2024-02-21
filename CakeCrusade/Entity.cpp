// Entity.cpp
#include "Entity.hpp"

// Entity 
Entity::Entity(float h, float d, float def)
    : health(h), damage(d), defense(def) {}

float Entity::getHealth() const { return health; }
float Entity::getDamage() const { return damage; }
float Entity::getDefense() const { return defense; }

void Entity::setHealth(float& h) { this->health = h; }
void Entity::setDamage(float& d) { this->damage = d; }
void Entity::setDefense(float& def) { this->defense = def; }

void Entity::attackMove() {
    // Implementation here
}
