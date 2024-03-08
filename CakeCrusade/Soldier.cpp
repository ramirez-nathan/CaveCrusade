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
    // check if texture loaded correctly
    if (!Texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png"))
    {
        std::cerr << "Soldier texture failed to load!" << std::endl;
    }
    SpriteX = 0;
    SpriteY = 0;
    // set texture
    Sprite.setTexture(Texture);
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
// takes parameters : delta time, player position, level
void Soldier::update(double deltaTime, const sf::Vector2f& target, int level[])
{
    vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    if (Health > 0)
    {
        Direction = Math::normalizeVector(target - Sprite.getPosition());

        sf::Vector2f Position = Sprite.getPosition();
        sf::Vector2f Movement(Direction * SoldierSpeed * static_cast<float>(deltaTime));

        sf::Vector2f Future = Position + Movement;

        int FuturePos = floor(Future.y / 64) * 23 + floor(Future.x / 64);
        if (!(std::find(Walls.begin(), Walls.end(), level[FuturePos]) != Walls.end())) {
            Sprite.setPosition(Position + Movement);
        }

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