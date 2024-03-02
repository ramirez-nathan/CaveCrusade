#include "Player.hpp"
#include "Math.hpp"
#include <math.h>
#include <ostream>
#include <algorithm>    // std::find

Player::Player(float h, float dmg, float def, float spd) 
   : Entity(h, def, dmg, spd), MaxFireRate(300), FireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::initialize()
{
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Red);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 32);
}

void Player::load()
{
    loadTexture("assets/player/textures/player_idle.png");
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    Sprite.setPosition(sf::Vector2f(600, 300));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 12);
    // change sprite scale
    Sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the player
    BoundingRectangle.setSize(sf::Vector2f(Size.x * Sprite.getScale().x, Size.y * Sprite.getScale().y));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getLocalBounds().width / 2.f, BoundingRectangle.getLocalBounds().height / 2.f);
}

// Separate function for handling player movement
void Player::handleMovement(const double deltaTime, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls) {
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Future = Position + movement;

    // Additional code for WASD movements
    if (direction == 1) {
        spriteX = 0;
        spriteY = 1;
    }
    else if (direction == 0) {
        spriteX = 0;
        spriteY = 0;
    }
    else if (direction == 2) {
        spriteX = 0;
        spriteY = 2;
    }
    else if (direction == 3) {
        spriteX = 0;
        spriteY = 3;
    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));

    int FuturePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + movement);
    }
}

// takes parameters - deltatime, any specified entity (by upcasting), mouseposition, and level
void Player::update(const double deltaTime, Entity& soldier, Entity& skeleton, Entity& slime, sf::Vector2f& mousePosition, int level[]) // add the level [], convert pos
{
    if (Health > 0) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f movement(0, -1 * EntitySpeed * static_cast<float>(deltaTime));
            handleMovement(deltaTime, movement, SpriteX, SpriteY, 1, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f movement(0, 1 * EntitySpeed * static_cast<float>(deltaTime));
            handleMovement(deltaTime, movement, SpriteX, SpriteY, 0, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f movement(-1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            handleMovement(deltaTime, movement, SpriteX, SpriteY, 2, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f movement(1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            handleMovement(deltaTime, movement, SpriteX, SpriteY, 3, level, Walls);
        }

        //---------------------------------------------- ARROWS -------------------------------------------------
        handleArrow(deltaTime, soldier, skeleton, slime, mousePosition, FireRateTimer, MaxFireRate, level, Walls);
        //---------------------------------------------- ARROWS -------------------------------------------------
        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Player::handleArrow(const double deltaTime, Entity& soldier, Entity& skeleton, Entity& slime, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls) 
{
    FireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && FireRateTimer >= MaxFireRate)
    {
        Arrows.push_back(Arrow());
        int i = Arrows.size() - 1;
        Arrows[i].initialize(Sprite.getPosition(), mousePosition, 0.5f);
        FireRateTimer = 0;
    }

    for (size_t i = 0; i < Arrows.size(); i++)
    {
        if (Arrows[i].didArrowHitWall(deltaTime, walls, level))
        {
            Arrows.erase(Arrows.begin() + i);
        }
        else {
            Arrows[i].update(deltaTime);
            if (soldier.getHealth() > 0 && Arrows.size() > 0)
            {
                // implement this when collision is finished
                if (Math::didRectCollide(Arrows[i].getArrowGlobalBounds(), soldier.getHitBox().getGlobalBounds()))
                {
                    if (soldier.getDefense() > 0) {
                        soldier.changeDefense(-25);
                    }
                    else {
                        soldier.changeHealth(-25);
                    }
                    Arrows.erase(Arrows.begin() + i);
                    cout << "Soldier's health is: " << soldier.getHealth() << endl;
                    continue;
                }
            }
            if (skeleton.getHealth() > 0 && Arrows.size() > 0)
            {
                // implement this when collision is finished
                if (Math::didRectCollide(Arrows[i].getArrowGlobalBounds(), skeleton.getHitBox().getGlobalBounds()))
                {
                    if (skeleton.getDefense() > 0) {
                        skeleton.changeDefense(-25);
                    }
                    else {
                        skeleton.changeHealth(-25);
                    }
                    Arrows.erase(Arrows.begin() + i);
                    cout << "Skeleton's health is: " << skeleton.getHealth() << endl;
                    continue;
                }
            }
            if (slime.getHealth() > 0 && Arrows.size() > 0)
            {
                // implement this when collision is finished
                if (Math::didRectCollide(Arrows[i].getArrowGlobalBounds(), slime.getHitBox().getGlobalBounds()))
                {
                    if (slime.getDefense() > 0) {
                        slime.changeDefense(-25);
                    }
                    else {
                        slime.changeHealth(-25);
                    }
                    Arrows.erase(Arrows.begin() + i);
                    cout << "Slime's health is: " << slime.getHealth() << endl;
                    continue;
                }
            }
        }
    }
}

void Player::drawPlayer(sf::RenderWindow& window)
{
    if (Health > 0) {
        window.draw(Sprite);
        window.draw(BoundingRectangle);
        // draw each arrow sprite in vector
        for (size_t i = 0; i < Arrows.size(); i++)
            Arrows[i].drawArrow(window);
    }
}

void Player::attackMove() {
    cout << "Player attack works!" << endl;
}