//psudo-ish code for enemy class
#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def) : Entity(h, dmg, def) {
    // Constructor implementation can initialize any additional members here
    //:Health(h), Damage(dmg), Defense(def) {}
}

void Enemy::attackMove() {
    //Implement how the enemy attacks

    //if (distance between the two is 0) {
        //player.ChangeHealth();
        //player.setDamage();
        //player.setDefense();
    //}
}

bool Enemy::canAttack(const sf::Vector2f& playerPosition, float attackRange) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = sprite.getPosition();

    //Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    //Check if the distance is within the specified attack range
    return distance <= attackRange;
}

void Enemy::getKnockedBack() {
   //Implement the logic for getting knocked back
   if (canAttack(sprite.getPosition(), 3) == true) {
        
        sf::Vector2f currentPosition = sprite.getPosition();
        sf::Vector2f knockbackDirection = currentPosition;
            //sprite.playerPosition();
        sf::Vector2f newPosition = sf::Vector2f(currentPosition - knockbackDirection);
        sprite.setPosition(newPosition);
   }
}

void Enemy::target() {
    // Implement the logic for targeting

}
