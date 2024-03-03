#include "Slime.hpp"
#include <iostream>

Slime::Slime(float h, float dmg, float def, float spd) 
	: Entity(h, dmg, def, spd) {}

void Slime::load() {
    loadTexture("assets/enemies/Slime/slime_idle.png");
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f);
    // change sprite scale
    Sprite.scale(sf::Vector2f(4, 4));
    // wrap the hitbox around the soldier
    BoundingRectangle.setSize(sf::Vector2f(Size.x * Sprite.getScale().x, Size.y * Sprite.getScale().y));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f);
}

void Slime::initialize() {
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Red);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 16);
}

void Slime::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls)
{
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Movement(Direction * EntitySpeed * static_cast<float>(deltaTime));
    sf::Vector2f Future = Position + Movement;

    // Additional code for WASD movements
    if ((direction.x == 0.f && direction.y > 0.f) || (direction.x != 0.f && direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        spriteX = 1;
        spriteY = 0;

    }
    else if ((direction.x > 0.f && direction.y == 0.f) || (direction.x > 0.f && (-0.50f <= direction.y && direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        spriteX = 2;
        spriteY = 0;

    }
    else if ((direction.x < 0.f && direction.y == 0.f) || (direction.x < 0.f && (-0.5f <= direction.y && direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 0;

    }
    else if ((direction.x == 0.f && direction.y < 0.f) || (direction.x != 0.f && direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        spriteX = 3;
        spriteY = 0;

    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));

    int FuturePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + Movement);
    }
}

void Slime::attackMove() {
    cout << "Slime attack works!" << endl;
}