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

void Soldier::attackAnimation(const sf::Vector2f& playerPosition)
{
    sf::Time elapsedTime = attackClock.getElapsedTime();
    sf::Vector2f enemyPosition = Sprite.getPosition();
    float deltaX = playerPosition.x - enemyPosition.x;
    float deltaY = playerPosition.y - enemyPosition.y;

    const sf::IntRect rectRightA(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing down aggro
    const sf::IntRect rectLeftA(1 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing down swing
    const sf::IntRect rectDownA(2 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing down swing 2
    const sf::IntRect rectUpA(3 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);    // Facing down swing 3

    const sf::IntRect rectRightB(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing up aggro
    const sf::IntRect rectLeftB(1 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing up swing
    const sf::IntRect rectDownB(2 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing up swing
    const sf::IntRect rectUpB(3 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);    // Facing up swing

    const sf::IntRect rectRightC(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing right aggro
    const sf::IntRect rectLeftC(1 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing right swing
    const sf::IntRect rectDownC(2 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing right swing 2
    const sf::IntRect rectUpC(3 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);    // Facing right swing 3

    const sf::IntRect rectRightD(0 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight); // Facing left aggro
    const sf::IntRect rectLeftD(1 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing left swing
    const sf::IntRect rectDownD(2 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);  // Facing left swing 2
    const sf::IntRect rectUpD(3 * spriteWidth, 0 * spriteHeight, spriteWidth, spriteHeight);    // Facing left swing 3

    


    // This determines if our player is in the range for enemies to get aggressive
    if (isAgressive(playerPosition)) {
        Sprite.setTexture(attackTexture);
        // Player is to the right
        if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {
            //Sprite.setTextureRect(rectRightA);
        }
        // Player is to the left 
        else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {
            //Sprite.setTextureRect(rectLeftB);
        }
        // Player is below
        else if (deltaY > 0) {
            //Sprite.setTextureRect(rectDownC);
        }
        // Player is above
        else {
            //Sprite.setTextureRect(rectUpD);
        }
    }


    if (canAttack(playerPosition) && elapsedTime.asMilliseconds() > attackCooldown) {
        Sprite.setTexture(attackTexture);
        // Player is to the right
        if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {
           
        }
        // Player is to the left 
        else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {

        }
        // Player is below
        else if (deltaY > 0) {
            
        }
        // Player is above
        else {
            
        }
        //Sprite.setTexture(attackTexture);
        //SpriteX = SwingingSpriteX;
        //SpriteY = SwingingSpriteY;
        //Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
        
        cout << "Enemy attack animation playing" << endl;


        attackClock.restart();
        //Sprite.setTexture(Texture);
    }
}


