#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float d) 
	: Entity(h, d)
{
}

Soldier::~Soldier()
{
}

void Soldier::ChangeHealth(float hp)
{
	health += hp;
}

void Soldier::Initialize()
{
	soldierSprite.setOrigin(soldierSprite.getLocalBounds().width / 2.f, soldierSprite.getLocalBounds().height / 2.f);
	size = sf::Vector2i(32, 32);
}

void Soldier::Load() {
    // check if texture loaded correctly
    if (!texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png"))
    {
        std::cerr << "Soldier texture failed to load!" << std::endl;
    }
    XIndex = 0;
    YIndex = 0;
    // set texture
    soldierSprite.setTexture(texture);
    // grab the idle texture image from spritesheet
    soldierSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
    // set spawn position
    soldierSprite.setPosition(sf::Vector2f(500, 200));
    // change sprite scale
    soldierSprite.scale(sf::Vector2f(3, 3));
}

void Soldier::Update(double deltaTime)
{
    if (health > 0)
    {
        /*boundingRectangle.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition()); */
    }
}

void Soldier::Draw(sf::RenderWindow& window)
{ 
    if (health > 0)
    {
        window.draw(soldierSprite);
    }
}
