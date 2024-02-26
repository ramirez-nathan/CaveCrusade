#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def) : Entity(h, dmg, def) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove() {
    // Implement how the enemy attacks
}

void Enemy::getKnockedBack() {
    // Implement the logic for getting knocked back
}

void Enemy::target() {
    // Implement the logic for targeting
}
