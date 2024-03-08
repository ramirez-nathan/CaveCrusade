#include "Player.hpp"
#include "Math.hpp"
#include <math.h>
#include <ostream>
#include <algorithm>    // std::find

Player::Player(float h, float dmg, float def, float spd) 
   : Entity(h, dmg, def, spd), MaxFireRate(500), FireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::initialize()
{
    BoundingRectangle.setFillColor(sf::Color::Transparent);
    BoundingRectangle.setOutlineColor(sf::Color::Blue);
    BoundingRectangle.setOutlineThickness(1);

    Size = sf::Vector2i(32, 32);
}

void Player::load()
{
    if (!Texture.loadFromFile("assets/player/textures/player_idle.png")) {
        std::cerr << "Failed to load texture from " << "assets/player/textures/player_idle.png" << std::endl;
    }
    Sprite.setTexture(Texture);
    if (!ShootingTexture.loadFromFile("assets/player/textures/player_attacking_bow.png"))
        std::cerr << "Failed to load texture from " << "assets/player/textures/player_attacking_bow.png" << std::endl;
    if (!WalkingTexture.loadFromFile("assets/player/textures/player_walking.png"))
        std::cerr << "Failed to load texture from " << "assets/player/textures/player_walking.png" << std::endl;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set spawn position
    Sprite.setPosition(sf::Vector2f(704, 600));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 12);
    // change sprite scale
    Sprite.scale(sf::Vector2f(3, 3));
    // wrap the hitbox around the player
    BoundingRectangle.setSize(sf::Vector2f(Size.x * (Sprite.getScale().x - 1), Size.y * (Sprite.getScale().y - 1)));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getLocalBounds().width / 2.f, BoundingRectangle.getLocalBounds().height / 2.f + 17);
}

// Separate function for handling player movement
void Player::handleMovement(const double deltaTime, bool& isMoving, sf::Clock& walkingClock, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls) {
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Future = Position + movement;
    IsMoving = true; // player will move, so set to true
    walkingAnimation(walkingClock, direction);
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

    int FuturePos = floor(Future.y / 64) * 23 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + movement);
    }
}

// takes parameters - deltatime, any specified entity (by upcasting), mouseposition, and level
void Player::playerUpdate(const double deltaTime, sf::Clock& idleAnimationClock, sf::Clock& shootingClock, sf::Clock& walkingClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int level[]) // add the level [], convert pos
{
    if (Health > 0) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            sf::Vector2f position = Sprite.getPosition();
            cout << position.x << endl;
            cout << position.y << endl;
        }
        
        UpdateHandlingComplete = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sf::Vector2f movement(0, -1 * EntitySpeed * static_cast<float>(deltaTime));
            PlayerDirection = 1;
            handleMovement(deltaTime, IsMoving, walkingClock, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sf::Vector2f movement(0, 1 * EntitySpeed * static_cast<float>(deltaTime));
            PlayerDirection = 0;
            handleMovement(deltaTime, IsMoving, walkingClock, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2f movement(-1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            PlayerDirection = 2;
            handleMovement(deltaTime, IsMoving, walkingClock, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sf::Vector2f movement(1 * EntitySpeed * static_cast<float>(deltaTime), 0);
            PlayerDirection = 3;
            handleMovement(deltaTime, IsMoving, walkingClock, movement, SpriteX, SpriteY, PlayerDirection, level, Walls);
        }

        if (!IsMoving) {
            if (idleAnimationClock.getElapsedTime().asSeconds() > 0.5f) {
                if (IdleSpriteX == 1)
                    IdleSpriteX = 0;
                else
                    IdleSpriteX += 1;
                idleAnimationClock.restart();
            }
        }
        
        //---------------------------------------------- ARROWS -------------------------------------------------
        handleArrow(deltaTime, shootingClock, enemies, mousePosition, FireRateTimer, MaxFireRate, level, Walls);
        //---------------------------------------------- ARROWS -------------------------------------------------
        UpdateHandlingComplete = true;

        //------------------------------------- LOAD CORRECT TEXTURE AND SPRITE INDEXES -----------------------------------
        if (UpdateHandlingComplete) {
            if (ShootingArrow) { // takes precedence over the other ones
                Sprite.setTexture(ShootingTexture); 
                // set these to prepare for rendering the right sprite 
                SpriteX = ShootingSpriteX; 
                SpriteY = ShootingSpriteY; 
            }
            else if (IsMoving) { // walking 
                Sprite.setTexture(WalkingTexture); 
                SpriteX = WalkingSpriteX; 
                SpriteY = WalkingSpriteY; 
            } 
            else {
                Sprite.setTexture(Texture);
                SpriteX = IdleSpriteX;
            }
        }
        IsMoving = false; // set it back to false after the movement to reset the bool for next loop
        //------------------------------------- LOAD CORRECT TEXTURE -----------------------------------
        Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Player::handleArrow(const double deltaTime, sf::Clock& shootingClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls)
{
    FireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && FireRateTimer >= MaxFireRate && Ammo > 0) 
    { 
        ShootingArrow = true; 
        arrowShootAnimation(shootingClock, mousePosition); // call the animation while holding down mouse button 
        if (ShootingAnimationComplete) { // once the first animation finishes, the arrow will be pushed into the vector and drawn 
            Arrows.push_back(Arrow()); 
            int i = Arrows.size() - 1; 
            Arrows[i].initialize(Sprite.getPosition(), mousePosition, 0.5f); 
            Ammo--;
            cout << "Your Ammo is: " << Ammo << endl;
            FireRateTimer = 0; 
        } 
    } 
    else { 
        ShootingArrow = false; 
    } 
    // iterate through the arrows in reverse order
    for (size_t i = Arrows.size(); i > 0; i--) 
    {
        if (Arrows[i - 1].didArrowHitWall(deltaTime, walls, level))
        {
            // if an arrow hits a wall, erase it from the vector
            Arrows.erase(Arrows.begin() + (i - 1));
            continue; // continue to next loop iteration
        }
        // update arrow position
        Arrows[i - 1].update(deltaTime); 

        // check for collisions with enemies
        for (size_t j = 0; j < enemies.size(); ++j) {
            if (enemies[j]->getHealth() > 0) {
                if (Math::didRectCollide(Arrows[i - 1].getArrowGlobalBounds(), enemies[j]->getHitBox().getGlobalBounds()))
                {
                    if (enemies[j]->getDefense() > 0) {
                        enemies[j]->changeDefense(-40); // Arrow dmg is 40
                    }
                    else {
                        enemies[j]->changeHealth(-40);
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


void Player::walkingAnimation(sf::Clock& walkingClock, int direction) {
    if (IsMoving) {
        if (direction == 0) { // Looking Down, Looking Down Diagonally
            WalkingSpriteY = 0;
        }
        if (direction == 3) { // Looking Right, Looking Right Diagonally
            WalkingSpriteY = 3;
        }
        if (direction == 2) { // Looking Left, Looking Left Diagonally
            WalkingSpriteY = 2;
        }
        if (direction == 1) { // Looking Up, Looking Up Diagonally
            WalkingSpriteY = 1;
        }
        WalkingAnimationComplete = false;
        if (walkingClock.getElapsedTime().asSeconds() > 0.25f) {
            if (WalkingSpriteX == 3) {
                WalkingAnimationComplete = true;
                WalkingSpriteX = 0;
            }
            else {
                WalkingSpriteX++;
            }
            walkingClock.restart();
        }
    }
}

// takes parameters shootingClock, mousePosition
void Player::arrowShootAnimation(sf::Clock& shootingClock, sf::Vector2f mouseDirection) {
    mouseDirection = Math::normalizeVector(mouseDirection - Sprite.getPosition());
    
    if (ShootingArrow) {
        if ((mouseDirection.x == 0.f && mouseDirection.y > 0.f) || (mouseDirection.x != 0.f && mouseDirection.y > 0.5f)) { // Looking Down, Looking Down Diagonally
            ShootingSpriteY = 0;
        } 
        if ((mouseDirection.x > 0.f && mouseDirection.y == 0.f) || (mouseDirection.x > 0.f && (-0.50f <= mouseDirection.y && mouseDirection.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
            ShootingSpriteY = 3; 
        } 
        if ((mouseDirection.x < 0.f && mouseDirection.y == 0.f) || (mouseDirection.x < 0.f && (-0.5f <= mouseDirection.y && mouseDirection.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
            ShootingSpriteY = 2;
        } 
        if ((mouseDirection.x == 0.f && mouseDirection.y < 0.f) || (mouseDirection.x != 0.f && mouseDirection.y < -0.5f)) { // Looking Up, Looking Up Diagonally
            ShootingSpriteY = 1;
        } 
        ShootingAnimationComplete = false;
        if (shootingClock.getElapsedTime().asSeconds() > 0.25f) { 
            if (FinishedBowAnimation) { 
                ShootingAnimationComplete = true; 
                ShootingArrow = false; 
                FinishedBowAnimation = false; 
            } 
            else if (ShootingSpriteX == 0) { // do nothing, just set shootingspritex up for the next time player shoots 
                FinishedBowAnimation = true;
                ShootingSpriteX = 1; // set it to next frame 
            }
            else {
                ShootingSpriteX--; // set shootingspritex to 0 for first frame
            }
            /*Sprite.setTexture(ShootingTexture);
            cout << "Setting Texture to Shooting" << endl;*/
            shootingClock.restart(); // restart so that we can check if a quarter second passed again in the next loop or so
        }
    }
}


bool Player::isTouchingDoor(int level[])
{
    sf::Vector2f position = Sprite.getPosition();
    
    int currPos = floor(position.y / 64) * 23 + floor(position.x / 64);

    if (level[currPos] == 25 || level[currPos] == 26 || level[currPos] == 27) {
        return true;
    }

    return false;
}
