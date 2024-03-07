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
    Sprite.setPosition(sf::Vector2f(704, 600));
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

    

    int FuturePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + movement);
    }
}

// takes parameters - deltatime, any specified entity (by upcasting), mouseposition, and level
void Player::playerUpdate(const double deltaTime, sf::Clock& animationClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int level[]) // add the level [], convert pos
{
    int PlayerDirection;
    if (Health > 0) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // up
            sf::Vector2f movement(0, -1 * EntitySpeed * static_cast<float>(deltaTime));
            PlayerDirection = 1;
            handleMovement(deltaTime, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // down
            sf::Vector2f movement(0, 1 * EntitySpeed * static_cast<float>(deltaTime));
            PlayerDirection = 0;
            handleMovement(deltaTime, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // left
            sf::Vector2f movement(-1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            PlayerDirection = 2;
            handleMovement(deltaTime, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // right
            sf::Vector2f movement(1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            PlayerDirection = 3;
            handleMovement(deltaTime, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }
        if (animationClock.getElapsedTime().asSeconds() > 0.5f) {
            if (SpriteX == 1)
                SpriteX = 0;
            else
                SpriteX += 1;
            animationClock.restart();
        }
        
        Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
        //---------------------------------------------- ARROWS -------------------------------------------------
        handleArrow(deltaTime, enemies, mousePosition, PlayerDirection, FireRateTimer, MaxFireRate, level, Walls);
        //---------------------------------------------- ARROWS -------------------------------------------------
        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Player::handleArrow(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int& playerDirection, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls)
{
    FireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && FireRateTimer >= MaxFireRate)
    {
        Arrows.push_back(Arrow());
        int i = Arrows.size() - 1;
        Arrows[i].initialize(Sprite.getPosition(), mousePosition, 0.5f);
        FireRateTimer = 0;
    }

    // iterate through the arrows in reverse order
    for (size_t i = Arrows.size(); i > 0; i--) 
    {
        if (Arrows[i - 1].didArrowHitWall(deltaTime, walls, level))
        {
            // if an arrow hits a wall, erase it from the vector
            Arrows.erase(Arrows.begin() + (i - 1));
            continue;
        }

        Arrows[i - 1].update(deltaTime); 

        // check for collisions with enemies
        for (size_t j = 0; j < enemies.size(); ++j) {
            if (enemies[j]->getHealth() > 0) {
                if (Math::didRectCollide(Arrows[i - 1].getArrowGlobalBounds(), enemies[j]->getHitBox().getGlobalBounds()))
                {
                    if (enemies[j]->getDefense() > 0) {
                        enemies[j]->changeDefense(-25);
                    }
                    else {
                        enemies[j]->changeHealth(-25);
                    }

                    // erase the arrow from the vector
                    Arrows.erase(Arrows.begin() + (i - 1));

                    cout << "Enemy #" << j << "'s health is : " << enemies[j]->getHealth() << endl;
                    break;
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

void Player::attackMove(const double deltaTime, Entity& enemy) {
    cout << "HAZZAAHH" << endl;
}

void Player::arrowShootAnimation(const double deltaTime, int& direction) { // literal junk code, i cant figure out animations
    //timer += deltaTime;
    //if (timer >= frameAnimationPause)
    //{
        // Additional code for WASD movements
    if (direction == 0) { // Looking Down, Looking Down Diagonally
        ArrowSpriteX = 0;
        ArrowSpriteY = 0;

    }
    else if (direction == 3) { // Looking Right, Looking Right Diagonally
        ArrowSpriteX = 0;
        ArrowSpriteY = 2;

        }
    else if (direction == 2) { // Looking Left, Looking Left Diagonally
        ArrowSpriteX = 0;
        ArrowSpriteY = 2;

    }
    else if (direction == 1) { // Looking Up, Looking Up Diagonally
        ArrowSpriteX = 0;
        ArrowSpriteY = 1;

    }
    Sprite.setTextureRect(sf::IntRect(ArrowSpriteX * getSizeX(), ArrowSpriteY * getSizeY(), getSizeX(), getSizeY()));
    ArrowSpriteX++;
        // Reset the timer
        //timer = 0;
    //}
    if (ArrowSpriteX > 1) {
        ArrowSpriteX = 0;
    }
    animationOccured = true;
} 