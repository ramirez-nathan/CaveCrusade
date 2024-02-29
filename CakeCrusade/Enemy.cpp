#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove() {
    // Implement how the enemy attacks

}

bool Enemy::canAttack(const sf::Vector2f& playerPosition, float attackRange) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = sprite.getPosition();

    // Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the distance is within the specified attack range
    return distance <= attackRange;
}

void Enemy::attackAnimation()
{
    
}


void Enemy::getKnockedBack() {
    // Implement the logic for getting knocked back
    
}

void Enemy::target() {
    // Implement the logic for targeting
}

