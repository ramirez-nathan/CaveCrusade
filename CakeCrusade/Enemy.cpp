#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove(const double deltaTime, Entity& player) 
{
    AttackTimer += deltaTime;
    if (canAttack(player.getSprite().getPosition(), 75) && AttackTimer >= MaxAttackRate) {
        player.changeHealth(-20);
        cout << "You've been hit!" << endl;
        cout << "Player's health is now " << player.getHealth() << endl;
        AttackTimer = 0;
    }
}

bool Enemy::canAttack(const sf::Vector2f& playerPosition, float attackRange) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = Sprite.getPosition();

    // Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the distance is within the specified attack range
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


void Enemy::getKnockedBack() {
    // Implement the logic for getting knocked back
    
}

