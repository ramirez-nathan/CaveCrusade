#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float d) 
	: Entity(h, d)
{
}

Soldier::~Soldier()
{
}

void Soldier::Initialize()
{
    setSize(sf::Vector2i(32, 32));
}

void Soldier::Load() {
    // check if texture loaded correctly
    if (!texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png"))
    {
        std::cerr << "Soldier texture failed to load!" << std::endl;
    }
    SpriteX = 0;
    SpriteY = 0;
    // set texture
    soldierSprite.setTexture(texture);
    // grab the idle texture image from spritesheet
    soldierSprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    soldierSprite.setPosition(sf::Vector2f(500, 200));
    // set origin at middle of sprite
    soldierSprite.setOrigin(soldierSprite.getLocalBounds().width / 2.f, soldierSprite.getLocalBounds().height / 2.f);
    // change sprite scale
    soldierSprite.scale(sf::Vector2f(3, 3));
}

void Soldier::Update(double deltaTime)
{
    if (health > 0)
    {
        /*boundingRectangle.setPosition(soldierSprite.getPosition());
        healthText.setPosition(soldierSprite.getPosition()); */
    }
}

void Soldier::Draw(sf::RenderWindow& window)
{ 
    if (health > 0)
    {
        window.draw(soldierSprite);
    }
}
