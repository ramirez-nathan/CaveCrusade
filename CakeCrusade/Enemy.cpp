//psudo-ish code for enemy class
#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
    : Health(h), Damage(dmg), Defense(def) {}
}

void Enemy::attackMove(player) {
    // Implement how the enemy attacks
    player.getPosition();
    enemyPosition = getPosition();
    playerPosition - enemyPosition;

}

void Enemy::getKnockedBack() {
    // Implement the logic for getting knocked back
    sf::Vector2f currentPosition = sprite.getPosition();
    knockbackDirection =
        sf::Vector2f newPosition = sf::Vector2f(currentPosition.x + knockbackDirection, currentPosition.y)
        sprite.setPosition(newPosition);
}

void Enemy::target() {
    // Implement the logic for targeting
}