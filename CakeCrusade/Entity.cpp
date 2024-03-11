// Entity.cpp
#include "Entity.hpp"
#include <iostream>

// Entity 
Entity::Entity(float h, float dmg, float def, float spd)
    : Health(h), Damage(dmg), Defense(def), EntitySpeed(spd), MaxHealth(h)
{
}


void Entity::loadTexture(const std::string& texturePath) {
    if (!Texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from " << texturePath << std::endl;
    }
    Sprite.setTexture(Texture);
}

void Entity::changePosition(float x, float y)
{
    Sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::initialize()
{
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Red);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 32);
}

void Entity::load()
{
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 14);
    // change sprite scale
    Sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the soldier
    BoundingRectangle.setSize(sf::Vector2f(Size.x * (Sprite.getScale().x - 1.2), Size.y * (Sprite.getScale().y - 1.1)));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f + 26);
}

void Entity::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls)
{
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Movement(Direction * EntitySpeed * static_cast<float>(deltaTime)); 
    sf::Vector2f Future = Position + Movement;

    // Additional code for WASD movements
    if ((direction.x == 0.f && direction.y > 0.f) || (direction.x != 0.f && direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        spriteX = 0;
        spriteY = 0;

    }
    else if ((direction.x > 0.f && direction.y == 0.f) || (direction.x > 0.f && (-0.50f <= direction.y && direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        spriteX = 0;
        spriteY = 3;

    }
    else if ((direction.x < 0.f && direction.y == 0.f) || (direction.x < 0.f && (-0.5f <= direction.y && direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 2;

    }
    else if ((direction.x == 0.f && direction.y < 0.f) || (direction.x != 0.f && direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        spriteX = 0;
        spriteY = 1;

    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));

    int FuturePos = floor(Future.y / 64) * 23 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) { 
        Sprite.setPosition(Position + Movement);
    }
}

// takes parameters : delta time, player, player position, level
void Entity::update(double deltaTime, sf::Clock& idleAnimationClock, Entity& player, const sf::Vector2f& target, int level[])
{
    if (Health > 0)
    {
        Direction = Math::normalizeVector(target - Sprite.getPosition());
        handleMovement(deltaTime, Direction, SpriteX, SpriteY, level, Walls);

        BoundingRectangle.setPosition(Sprite.getPosition());
    }

}


void Entity::draw(sf::RenderWindow& window)
{
    if (Health > 0)
    {
        window.draw(Sprite);
        //window.draw(BoundingRectangle);
    }
}


/*void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}*/


void Entity::getKnockedBack(const sf::Vector2f& attackerPosition, int level[], vector<int>& walls) {
    sf::Vector2f currentPosition = Sprite.getPosition();
    sf::Vector2f attackDirection = currentPosition - attackerPosition;
    float magnitude = std::sqrt(attackDirection.x * attackDirection.x + attackDirection.y * attackDirection.y);

    if (isAttacked() && magnitude > 0.0f) {
        sf::Vector2f normalizedDirection = attackDirection / magnitude;

        // Define the increment for each step (smaller values for higher precision)
        float stepSize = 5.0f; // Adjust based on your needs
        int steps = static_cast<int>(knockbackDistance / stepSize);
        sf::Vector2f increment = normalizedDirection * stepSize;

        // Move in increments, checking for collisions at each step
        for (int i = 0; i < steps; ++i) {
            sf::Vector2f testPosition = currentPosition + increment;

            int futurePosX = floor(testPosition.x / 64);
            int futurePosY = floor(testPosition.y / 64);
            int futurePosIndex = futurePosY * 22 + futurePosX; // Adjust the 22 based on your level width

            if (std::find(walls.begin(), walls.end(), level[futurePosIndex]) == walls.end()) {
                // No collision, update currentPosition
                currentPosition = testPosition;
            }
            else {
                // Collision detected, stop the movement
                break;
            }
        }

        // Set the final position after checking for collisions
        Sprite.setPosition(currentPosition);
        std::cout << "Entity was knocked back with collision checking." << std::endl;
    }
}




bool Entity::isAttacked() const
{
    return this->getHealth() < this->MaxHealth;
}