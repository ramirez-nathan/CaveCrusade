#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def, float spd, float rng)
	: Enemy(h, dmg, def, spd), MaxSwingRate(500), SwingRateTimer(0)
{
}

void Soldier::load() {
    // Load the idle texture
    if (!Texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png")) {
        cout << "Cannot load idle texture" << endl;
    }
    else {
        // If loading succeeds, set the sprite to use the idle texture initially
        Sprite.setTexture(Texture);
    }

    // Load the attacking texture
    if (!AttackTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }

    if (!WalkingTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_walking.png"))
        std::cerr << "Failed to load texture from " << "assets/enemies/evil_soldier/textures/evil_soldier_walking.png" << std::endl;
    // Call the load method of the base class if necessary
    Entity::load();
}

void Soldier::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) {
    if (Health > 0)
    {
        UpdateHandlingComplete = false;
        Direction = Math::normalizeVector(target - Sprite.getPosition());
        if ((Direction.x == 0.f && Direction.y > 0.f) || (Direction.x != 0.f && Direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
            EntityDirection = 0;
        }
        else if ((Direction.x > 0.f && Direction.y == 0.f) || (Direction.x > 0.f && (-0.50f <= Direction.y && Direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
            EntityDirection = 3;

        }
        else if ((Direction.x < 0.f && Direction.y == 0.f) || (Direction.x < 0.f && (-0.5f <= Direction.y && Direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
            EntityDirection = 2;

        }
        else if ((Direction.x == 0.f && Direction.y < 0.f) || (Direction.x != 0.f && Direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
            EntityDirection = 1;
        }
        handleMovement(deltaTime, Direction, SpriteX, SpriteY, EntityDirection, level, Walls);
        
        sf::Vector2f playerDirection = player.getSprite().getPosition();

        

        handleSword(deltaTime, player, playerDirection, level, Walls);
        
        UpdateHandlingComplete = true;
        //------------------------------------- LOAD CORRECT TEXTURE AND SPRITE INDEXES -----------------------------------
        if (UpdateHandlingComplete) {
            if (IsAttacking) {
                Sprite.setTexture(AttackTexture);
                SpriteX = AttackingSpriteX;
                SpriteY = AttackingSpriteY;
                Sprite.setTextureRect(sf::IntRect(SpriteX * (getSizeX() + 16), SpriteY * (getSizeY() + 16), (getSizeX() + 16), (getSizeY() + 16)));
            }
            else if (IsMoving && canAttack(playerDirection)) {
                makeAggressive(playerDirection);
            }
            else if (IsMoving) { // walking 
                Sprite.setTexture(WalkingTexture);
                SpriteX = WalkingSpriteX;
                SpriteY = WalkingSpriteY;
                Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
            }
            else { // if idle
                Sprite.setTexture(Texture);
                SpriteX = IdleSpriteX;
                Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
            }
        }
        IsMoving = false; // set it back to false after the movement to reset the bool for next loop
        //------------------------------------- LOAD CORRECT TEXTURE ----------------------------------- 
    }
    BoundingRectangle.setPosition(Sprite.getPosition());
}


void Soldier::attackMove(const double deltaTime, Entity& player) 
{
    cout << "HAVE AT THEE!!!" << endl;
}

void Soldier::handleSword(const double deltaTime, Entity& player, sf::Vector2f& playerPosition, int level[], vector<int>& walls) {
    SwingRateTimer += deltaTime;
    swingingAnimation();
    if (SwingRateTimer >= MaxSwingRate && canAttack(playerPosition))
    {
        IsAttacking = true;
        if (IsAttacking) {
            if (player.getHealth() > 0) {
                if (player.getDefense() > 0) {
                    player.changeDefense(-60); // Arrow dmg is 40
                }
                else {
                    player.changeHealth(-60);
                }
                cout << "You were slashed by a soldier! Your Health is: " << player.getHealth() << endl;

            }
            SwingRateTimer = 0;
        }
    }
}



bool Soldier::canAttack(const sf::Vector2f& playerPosition) const
{
    // Calculate the distance between the enemy and the player
    float Dx = Sprite.getPosition().x - playerPosition.x;
    float Dy = Sprite.getPosition().y - playerPosition.y;


    // Check if the enemy is within the cone angle in each direction
    if (AttackingSpriteY == 0) { // Looking Down, Looking Down Diagonally
        if ((Dx >= -70 && Dx <= 70) && (Dy >= -100 && Dy <= 0)) {
            return true;
        }
        return false;
    }
    else if (AttackingSpriteY == 3) { // Looking Right, Looking Right Diagonally
        if ((Dy <= 70 && Dy >= -70) && (Dx >= -100 && Dx <= 0)) {
            return true;
        }
        return false;
    }
    else if (AttackingSpriteY == 2) { // Looking Left, Looking Left Diagonally
        if ((Dy <= 70 && Dy >= -70) && (Dx <= 100 && Dx >= 0)) {
            return true;
        }
        return false;
    }
    else if (AttackingSpriteY == 1) { // Looking Up, Looking Up Diagonally
        if ((Dx >= -70 && Dx <= 70) && (Dy <= 100 && Dy >= 0)) {
            return true;
        }
        return false;
    }
}

void Soldier::swingingAnimation() {
    if (IsAttacking) {
        if (EntityDirection == 0) { // Looking Down, Looking Down Diagonally
            AttackingSpriteY = 0;
        }
        else if (EntityDirection == 3) { // Looking Right, Looking Right Diagonally
            AttackingSpriteY = 2; 
        }
        else if (EntityDirection == 2) { // Looking Left, Looking Left Diagonally
            AttackingSpriteY = 3;
        }
        else if (EntityDirection == 1) { // Looking Up, Looking Up Diagonally
            AttackingSpriteY = 1;
        }
        AttackingAnimationComplete = false;
        if (AttackClock.getElapsedTime().asSeconds() > 0.15f) {
            if (AttackingSpriteX == 3) { // do nothing, just set shootingspritex up for the next time player shoots 
                AttackingAnimationComplete = true;
                IsAttacking = false;
                AttackingSpriteX = 0; // set it to next frame 
            }
            else {
                AttackingSpriteX++; // set shootingspritex to 0 for first frame
            }
            AttackClock.restart();
        }
    }
}

bool Soldier::isAggressive(const sf::Vector2f& playerPosition) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = Sprite.getPosition();

    // Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the distance is within the specified attack range
    return distance <= this->aggressiveRange;
}

void Soldier::makeAggressive(const sf::Vector2f& playerPosition)
{
    sf::Vector2f enemyPosition = Sprite.getPosition();
    float deltaX = playerPosition.x - enemyPosition.x;
    float deltaY = playerPosition.y - enemyPosition.y;
    const sf::IntRect rectDownA(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing down aggro
    const sf::IntRect rectUpA(0 * spriteWidth, 1 * spriteHeight, spriteWidth, spriteHeight); // Facing up aggro
    const sf::IntRect rectRightA(0 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight); // Facing right aggro
    const sf::IntRect rectLeftA(0 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight); // Facing left aggro


    if (isAggressive(playerPosition)) {
        //cout << "Enemies are aggressive" << endl;
        Sprite.setTexture(AttackTexture);
        // Player is to the right
        if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectRightA);
        }
        // Player is to the left 
        else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectLeftA);
        }
        // Player is below
        else if (deltaY > 0) {
            Sprite.setTextureRect(rectDownA);
        }
        // Player is above
        else {
            Sprite.setTextureRect(rectUpA);
        }
    }
}

              

   