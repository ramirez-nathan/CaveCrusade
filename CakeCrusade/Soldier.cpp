#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def)
    : Entity(h, dmg, def), SoldierSpeed(0.2f)
{
}

Soldier::~Soldier()
{
}

void Soldier::initialize()
{
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Blue);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 32);
}

void Soldier::load()
{
    loadTexture("assets/enemies/evil_soldier/textures/evil_soldier_idle.png");
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    Sprite.setPosition(sf::Vector2f(500, 200));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f);
    // change sprite scale
    Sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the soldier
    BoundingRectangle.setSize(sf::Vector2f(Size.x * Sprite.getScale().x, Size.y * Sprite.getScale().y));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getLocalBounds().width / 2.f, BoundingRectangle.getLocalBounds().height / 2.f);
}

void Soldier::handleMovement(double deltaTime, sf::Vector2f& movement, int& spriteX, int& spriteY, int level[], vector<int>& walls)
{
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Future = Position + movement;

    // Additional code for WASD movements
    if ((movement.x == 0.f && movement.y > 0.f) || ((movement.x > 0.f || movement.x < 0.f) && movement.y > 100.0f)) { // Looking Down, Looking Down Diagonally
        spriteX = 0;
        spriteY = 0;
    }
    else if ((movement.x > 0.f && movement.y == 0.f) || (movement.x > 0.f && (-100.0f <= movement.y <= 100.0f))) { // Looking Right, Looking Right Diagonally
        spriteX = 0;
        spriteY = 3; 
    }
    else if ((movement.x < 0.f && movement.y == 0.f) || (movement.x < 0.f && (-100.0f <= movement.y <= 100.0f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 2; 
    }
    else if ((movement.x == 0.f && movement.y < 0.f) || ((movement.x > 0.f || movement.x < 0.f) && movement.y < -100.0f)) { // Looking Up, Looking Up Diagonally
        spriteX = 0;
        spriteY = 1;
    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));

    int FuturePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + movement);
    }
}

// takes parameters : delta time, player position, level
void Soldier::update(double deltaTime, const sf::Vector2f& target, int level[])
{
    if (Health > 0)
    {
        Direction = Math::normalizeVector(target - Sprite.getPosition());
        sf::Vector2f Movement(Direction * SoldierSpeed * static_cast<float>(deltaTime));
        handleMovement(deltaTime, Movement, SpriteX, SpriteY, level, Walls);

        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Soldier::drawSoldier(sf::RenderWindow& window)
{
    if (Health > 0)
    {
        window.draw(Sprite);
        window.draw(BoundingRectangle);
    }
}

void Soldier::attackMove() {
    // Implement how the enemy attacks
}