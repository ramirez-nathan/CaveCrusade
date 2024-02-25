// Entity.cpp
#include "Entity.hpp"

// Entity 
Entity::Entity(float h, float dmg, float def)
    : health(h), damage(dmg), defense(def) {}

float Entity::getHealth() const { return health; }
float Entity::getDamage() const { return damage; }
float Entity::getDefense() const { return defense; }

void Entity::setHealth(float& h) { this->health = h; }
void Entity::setDamage(float& dmg) { this->damage = dmg; }
void Entity::setDefense(float& def) { this->defense = def; }

void Entity::attackMove() {
    // Implementation here
}

bool Entity::loadTexture(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from " << texturePath << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void Entity::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

const sf::Vector2f& Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}