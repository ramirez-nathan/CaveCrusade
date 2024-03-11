#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def, float spd, float rng)
	: Enemy(h, dmg, def, spd), meleeRange(rng)
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
    if (!attackTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }

    // Call the load method of the base class if necessary
    Entity::load();
}


void Soldier::attackMove(const double deltaTime, Entity& player) 
{
    makeAggressive(player.getSprite().getPosition());
    AttackTimer += deltaTime;
    if (canAttack(player.getSprite().getPosition()) && AttackTimer >= MaxAttackRate) {
        player.changeHealth(-Damage);
        attackAnimation(player.getSprite().getPosition());
        cout << "You've been hit!" << endl;
        cout << "Player's health is now " << player.getHealth() << endl;
        AttackTimer = 0;
    }
}


bool Soldier::canAttack(const sf::Vector2f& playerPosition) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = Sprite.getPosition();

    // Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the distance is within the specified attack range
    return distance <= this->meleeRange;
}

bool Soldier::isAgressive(const sf::Vector2f& playerPosition) const
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


    if (isAgressive(playerPosition)) {
        //cout << "Enemies are aggressive" << endl;
        Sprite.setTexture(attackTexture);
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

void Soldier::attackAnimation(const sf::Vector2f& playerPosition)
{
    sf::Time elapsedTime = attackClock.getElapsedTime();
    sf::Vector2f enemyPosition = Sprite.getPosition();
    float deltaX = playerPosition.x - enemyPosition.x;
    float deltaY = playerPosition.y - enemyPosition.y;

    const sf::IntRect rectDownA(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing down aggro
    const sf::IntRect rectDownB(1 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing down swing
    const sf::IntRect rectDownC(2 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing down swing 2
    const sf::IntRect rectDownD(3 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);    // Facing down swing 3

    const sf::IntRect rectUpA(0 * spriteWidth, 1 * spriteHeight, spriteWidth, spriteHeight); // Facing up aggro
    const sf::IntRect rectUpB(1 * spriteWidth, 1 * spriteHeight, spriteWidth, spriteHeight);  // Facing up swing
    const sf::IntRect rectUpC(2 * spriteWidth, 1 * spriteHeight, spriteWidth, spriteHeight);  // Facing up swing
    const sf::IntRect rectUpD(3 * spriteWidth, 1 * spriteHeight, spriteWidth, spriteHeight);    // Facing up swing

    const sf::IntRect rectRightA(0 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight); // Facing right aggro
    const sf::IntRect rectRightB(1 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);  // Facing right swing
    const sf::IntRect rectRightC(2 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);  // Facing right swing 2
    const sf::IntRect rectRightD(3 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);    // Facing right swing 3

    const sf::IntRect rectLeftA(0 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight); // Facing left aggro
    const sf::IntRect rectLeftB(1 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);  // Facing left swing
    const sf::IntRect rectLeftC(2 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);  // Facing left swing 2
    const sf::IntRect rectLeftD(3 * spriteWidth, 2 * spriteHeight, spriteWidth, spriteHeight);    // Facing left swing 3

    

    if (canAttack(playerPosition) && elapsedTime.asMilliseconds() > attackCooldown) {
        // Sprite.setTexture(attackTexture);
        // Player is to the right
        if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectRightB);
            Sprite.setTextureRect(rectRightC);
            Sprite.setTextureRect(rectRightD);
        }
        // Player is to the left 
        else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectLeftB);
            Sprite.setTextureRect(rectLeftC);
            Sprite.setTextureRect(rectLeftD);
        }
        // Player is below
        else if (deltaY > 0) {
            Sprite.setTextureRect(rectLeftB);
            Sprite.setTextureRect(rectLeftC);
            Sprite.setTextureRect(rectLeftD);
        }
        // Player is above
        else {
            Sprite.setTextureRect(rectUpB);
            Sprite.setTextureRect(rectUpC);
            Sprite.setTextureRect(rectUpD);
        }
        
        
        cout << "Enemy attack animation playing" << endl;


        attackClock.restart();
        //Sprite.setTexture(Texture);
    }
}

void Soldier::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls)
{
    sf::Vector2f Position = Sprite.getPosition();
    sf::Vector2f Movement(Direction * EntitySpeed * static_cast<float>(deltaTime));
    sf::Vector2f Future = Position + Movement;

    // Additional code for WASD movements
    if ((direction.x == 0.f && direction.y > 0.f) || (direction.x != 0.f && direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        spriteX = 0;
        spriteY = 0;

    }
    else if ((direction.x > 0.f && direction.y == 0.f) || (direction.x > 0.f && (-0.50f <= direction.y && direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        spriteX = 0;
        spriteY = 3;

    }
    else if ((direction.x < 0.f && direction.y == 0.f) || (direction.x < 0.f && (-0.5f <= direction.y && direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 2;

    }
    else if ((direction.x == 0.f && direction.y < 0.f) || (direction.x != 0.f && direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        spriteX = 0;
        spriteY = 1;

    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));

    int FuturePos = floor(Future.y / 64) * 23 + floor(Future.x / 64);
    if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
        Sprite.setPosition(Position + Movement);
    }
}




