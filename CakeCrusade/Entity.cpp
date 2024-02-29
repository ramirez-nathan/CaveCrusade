// Entity.cpp
#include "Entity.hpp"
#include <iostream>

// Entity 
Entity::Entity(float h, float dmg, float def, float spd)
    : health(h), damage(dmg), defense(def), entitySpeed(spd)
{
}


bool Entity::loadTexture(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from " << texturePath << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void Entity::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(32, 32);
}

void Entity::Load()
{
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    sprite.setPosition(sf::Vector2f(500, 200));
    // set origin at middle of sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    // change sprite scale
    sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the soldier
    boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    // set hitbox origin to middle
    boundingRectangle.setOrigin(boundingRectangle.getLocalBounds().width / 2.f, boundingRectangle.getLocalBounds().height / 2.f);
}


// takes parameters : delta time, player position, level
void Entity::Update(double deltaTime, const sf::Vector2f& target, int level[])
{
    vector<int> walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    if (health > 0)
    {
        direction = Math::NormalizeVector(target - sprite.getPosition());

        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f movement(direction * entitySpeed * static_cast<float>(deltaTime));

        sf::Vector2f future = position + movement;

        int futurePos = floor(future.y / 64) * 22 + floor(future.x / 64);
        if (!(std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
            sprite.setPosition(position + movement);
        }

        boundingRectangle.setPosition(sprite.getPosition());
    }
}

void Entity::Draw(sf::RenderWindow& window)
{
    if (health > 0)
    {
        window.draw(sprite);
        window.draw(boundingRectangle);
    }
}

void Entity::changePosition(float x, float y)
{
    sprite.setPosition(sf::Vector2f(x, y));
}


/*void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}*/