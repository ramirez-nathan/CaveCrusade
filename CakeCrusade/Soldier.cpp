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

void Soldier::attackAnimation(const sf::Vector2f& playerPosition)
{
    sf::Time elapsedTime = attackClock.getElapsedTime();
    if (canAttack(playerPosition) && elapsedTime.asSeconds() > attackCooldown) {
        Sprite.setTexture(attackTexture);
        cout << "Enemy is attacking" << endl;


        attackClock.restart();
        Sprite.setTexture(Texture);
    }
}
