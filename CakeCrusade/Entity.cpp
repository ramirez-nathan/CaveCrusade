// Entity.cpp
#include "Entity.hpp"

// Entity 
Entity::Entity(float h, float dmg, float def)
    : Health(h), Damage(dmg), Defense(def) {}

void Entity::loadTexture(const std::string& texturePath) {
    if (!Texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from " << texturePath << std::endl;
    }
    Sprite.setTexture(Texture);
}

/*void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}*/