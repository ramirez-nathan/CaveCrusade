#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove(const double deltaTime, Entity& player) 
{
    AttackTimer += deltaTime;
    if (canAttack(player.getSprite().getPosition(), 50) && AttackTimer >= MaxAttackRate) {
        player.changeHealth(-Damage);
        cout << "You've been hit!" << endl;
        cout << "Player's health is now " << player.getHealth() << endl;
        AttackTimer = 0;
    }
}

bool Enemy::canAttack(const sf::Vector2f& playerPosition, float attackRange) const
{
    // get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = Sprite.getPosition();

    // calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // check if the distance is within the specified attack range
    return distance <= attackRange;
}

void Enemy::attackAnimation()
{
    cout << "Animation works!" << endl;
}

bool Enemy::isDead(const unique_ptr<Enemy>& entity)
{
    if (!entity->getHealth() > 0)
    {
        return true;
    }
    return false;
}


void Enemy::getKnockedBack(const sf::Vector2f& attackerPosition) {
    // Calculate the direction of the knockback
    sf::Vector2f attackDirection = Sprite.getPosition() - attackerPosition;
    float magnitude = std::sqrt(attackDirection.x * attackDirection.x + attackDirection.y * attackDirection.y);

    // Check if an attack actually occurred and if the magnitude is not zero (to avoid division by zero)
    if (isAttacked() && magnitude > 0.0f) {
        sf::Vector2f normalizedDirection = attackDirection / magnitude;

        // Calculate the new position using the knockback distance
        sf::Vector2f newPosition = Sprite.getPosition() + normalizedDirection * knockbackDistance; // knockback moves the enemy away, so it's `+`, not `-`

        // Set the enemy's position to the new position to simulate knockback
        Sprite.setPosition(newPosition);
        std::cout << "Enemy was knocked back." << std::endl;
    }
}



bool Enemy::isAttacked() const
{
    return this->getHealth() < this->MaxHealth;
}





