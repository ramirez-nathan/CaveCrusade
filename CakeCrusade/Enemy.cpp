#include "Enemy.hpp"

Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove() {
    // Implement how the enemy attacks

}

bool canAttack() {
    // checks to see if enemy is in range to attack
}

void Enemy::getKnockedBack() {
    // Implement the logic for getting knocked back
}

void Enemy::target() {
    // Implement the logic for targeting
}
