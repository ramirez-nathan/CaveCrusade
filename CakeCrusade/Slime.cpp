#include "Slime.hpp"
#include <iostream>

Slime::Slime(float h, float dmg, float def, float spd) 
	: Enemy(h, dmg, def, spd) {}

void Slime::load() {
    loadTexture("assets/enemies/Slime/slime_idle.png");
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 6);
    // change sprite scale
    Sprite.scale(sf::Vector2f(4.5, 4.5));
    // wrap the hitbox around the soldier
    BoundingRectangle.setSize(sf::Vector2f((Size.x - 6) * (Sprite.getScale().x - 1), (Size.y + 3) * (Sprite.getScale().y - 1)));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f + 21);
}

void Slime::initialize() {
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Red);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 16);
}

void Slime::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int entityDirection, int level[], vector<int>& walls)
{
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Movement(Direction * EntitySpeed * static_cast<float>(deltaTime));
    sf::Vector2f Future = Position + Movement;

    if (EnemyIdleClock.getElapsedTime().asSeconds() > 0.35f) {
        if (spriteX == 3)
            spriteX = 0;
        else
            spriteX += 1;
        EnemyIdleClock.restart();
    }

    int FuturePos = floor(Future.y / 64) * 23 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + Movement);
    }
}
