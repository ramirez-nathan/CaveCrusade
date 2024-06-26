#include "Enemy.hpp"
#include "SoundFx.hpp"



Enemy::Enemy(float h, float dmg, float def, float spd) : Entity(h, dmg, def, spd) {
    // Constructor implementation can initialize any additional members here
}

void Enemy::attackMove(const double deltaTime, Entity& player) 
{ 
    SoundFx sound;
    AttackTimer += deltaTime;
    if (canAttack(player.getSprite().getPosition(), 70) && AttackTimer >= MaxAttackRate) {
        player.changeHalfHearts(-1);
        
        cout << "You've been hit!" << endl;
        cout << "Player's half hearts is now " << player.getHalfHearts() << endl;
        sound.loadSound("sound/sounds/playerHurt.wav");
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

void Enemy::attackAnimation(const sf::Vector2f& playerPosition)
{
    cout << "Animation works!" << endl;
}

bool Enemy::isDead(const unique_ptr<Enemy>& entity)
{
    // if dead then call death animation first 
    // implement checking if death animation is finished yet 
    // maybe make another boolean called isReadyToDie() in which you call that function for the erasing enemies in main.cpp
    // and then have isDead be called at the end of the enemy update loop, in which if dead it would call the deathAnimation() function
    if (entity->getHealth() <= 0)
    {
        return true;
    }
    return false;
}










