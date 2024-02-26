#include "Player.hpp"
#include "Math.hpp"
#include <math.h>
#include <ostream>
#include <algorithm>    // std::find

Player::Player(float h, float dmg, float def) 
   : Entity(h, def, dmg), playerSpeed(0.4f), maxFireRate(300), fireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);

    size = sf::Vector2i(32, 32);
}

void Player::Load() 
{
    // check if texture loaded correctly
    if (!texture.loadFromFile("assets/player/textures/player_idle.png"))
    {
        std::cerr << "Player texture failed to load!" << std::endl;
    }
    // set texture
    sprite.setTexture(texture);
    // grab the idle texture image from spritesheet
    sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    sprite.setPosition(sf::Vector2f(600, 300));
    // set origin at middle of sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f + 12);
    // change sprite scale
    sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the player
    boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    // set hitbox origin to middle
    boundingRectangle.setOrigin(boundingRectangle.getLocalBounds().width / 2.f, boundingRectangle.getLocalBounds().height / 2.f);
}

// takes parameters - deltatime, any specified entity (by upcasting), mouseposition, and level
void Player::Update(double deltaTime, Entity& enemy, sf::Vector2f& mousePosition, int level[]) // add the level [], convert pos
{
    vector<int> walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    // WASD MOVEMENT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //(0,1)
    {
        SpriteX = 0;
        SpriteY = 1;
        sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));

        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f movement(0, -1 * playerSpeed * static_cast<float>(deltaTime));

        int playerX = floor(position.x / 64); // col
        int playerY = floor(position.y / 64); // row

        sf::Vector2f future = position + movement;

        int futurePos = floor(future.y / 64) * 22 + floor(future.x / 64);
        if (!(std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
            sprite.setPosition(position + movement);
        }   
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //(0,0)
    {
        SpriteX = 0;
        SpriteY = 0;
        sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));

        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f movement(0, 1 * playerSpeed * static_cast<float>(deltaTime));

        int playerX = floor(position.x / 64); // col
        int playerY = floor(position.y / 64); // row

        sf::Vector2f future = position + movement;

        int futurePos = floor(future.y / 64) * 22 + floor(future.x / 64);
        if (!(std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
            sprite.setPosition(position + movement);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // (0,2)
    {
        SpriteX = 0;
        SpriteY = 2;
        sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));

        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f movement(-1 * playerSpeed * static_cast<float>(deltaTime), 0);

        int playerX = floor(position.x / 64); // col
        int playerY = floor(position.y / 64); // row

        sf::Vector2f future = position + movement;

        int futurePos = floor(future.y / 64) * 22 + floor(future.x / 64);;
        if (!(std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
            sprite.setPosition(position + movement);
        }   
        
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //(0,3)
    {
        SpriteX = 0;
        SpriteY = 3;
        sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));

        sf::Vector2f position = sprite.getPosition();
        sf::Vector2f movement(1 * playerSpeed * static_cast<float>(deltaTime), 0);

        int playerX = floor(position.x / 64); // col
        int playerY = floor(position.y / 64); // row

        sf::Vector2f future = position + movement;

        int futurePos = floor(future.y / 64) * 22 + floor(future.x / 64);;
        if (!(std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
            sprite.setPosition(position + movement);
        }

    }

    //---------------------------------------------- ARROWS -------------------------------------------------
    fireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate)
    {
        arrows.push_back(Arrow());
        int i = arrows.size() - 1;
        arrows[i].Initialize(sprite.getPosition(), mousePosition, 0.5f);
        fireRateTimer = 0;
    }

    for (size_t i = 0; i < arrows.size(); i++)
    {
        arrows[i].Update(deltaTime);
        if (enemy.getHealth() > 0)
        {
            // implement this when collision is finished 
            if (Math::DidRectCollide(arrows[i].GetGlobalBounds(), enemy.getSprite().getGlobalBounds()))
            {
                enemy.ChangeHealth(-15);
                arrows.erase(arrows.begin() + i);
                cout << "Soldier's health is: " << enemy.getHealth() << endl;
            }
        }
    }

    //---------------------------------------------- ARROWS -------------------------------------------------
    boundingRectangle.setPosition(sprite.getPosition());

}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(boundingRectangle);
    // draw each arrow sprite in vector
    for (size_t i = 0; i < arrows.size(); i++)
        arrows[i].Draw(window);
}

void Player::attackMove() {
    // Implement how the enemy attacks
}