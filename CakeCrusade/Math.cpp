#include "Math.hpp"
#include "Player.hpp"

// normalize vector function; divides x and y by the magnitude
sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
	float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	sf::Vector2f normalizedVector;

	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
}

//todo: tile collision


// AABB Collision function
bool Math::DidRectCollide(sf::FloatRect rect1, sf::FloatRect rect2)
{
	if (rect1.left + rect1.width > rect2.left &&
		rect2.left + rect1.width > rect1.left &&
		rect2.top + rect2.height > rect1.top &&
		rect1.top + rect1.height > rect2.top)
		return true;

	return false;
}

void Math::Collider(Entity& player, Entity& enemy, int level[])
{
    vector<int> walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    sf::FloatRect playerHitbox = player.getBoundingRect().getGlobalBounds();
    sf::FloatRect enemyHitbox = enemy.getBoundingRect().getGlobalBounds();
    
    // Update player's position
    sf::Vector2f futurePlayerPos = player.getSprite().getPosition() + player.getMovement();
    int futurePlayerTile = floor(futurePlayerPos.y / 64) * 22 + floor(futurePlayerPos.x / 64);

    // Get the enemy's position and its future position
    sf::Vector2f enemyPos = enemy.getSprite().getPosition();
    sf::Vector2f enemyMovement = enemy.getMovement();
    sf::Vector2f futureEnemyPos = enemyPos + enemyMovement;
    int futureEnemyTile = floor(futureEnemyPos.y / 64) * 22 + floor(futureEnemyPos.x / 64);
    
    // Check if the player's future position collides with a wall
    if (std::find(walls.begin(), walls.end(), level[futurePlayerTile]) != walls.end())
    {
        ; // Don't move the player or the enemy
    }
    // Check if the player's future position collides with the enemy
    else if (Math::DidRectCollide(playerHitbox, enemyHitbox))
    {
        // Move the enemy to the next available tile
        if (!(std::find(walls.begin(), walls.end(), level[futureEnemyTile]) != walls.end()))
        {
            enemy.getSprite().setPosition(futureEnemyPos);
        }

        // If the player and enemy still collide after moving the enemy,
        // don't move the player
        playerHitbox = player.getBoundingRect().getGlobalBounds();
        if (Math::DidRectCollide(playerHitbox, enemyHitbox))
        {
            ; // Dont move the player
        }
        else
        {
            // Move the player
            player.getBoundingRect().setPosition(futurePlayerPos);
            player.getSprite().setPosition(futurePlayerPos);
        }
    }
    else
    {
        // Move the player
        player.getBoundingRect().setPosition(futurePlayerPos);
        player.getSprite().setPosition(futurePlayerPos);

        // Move the enemy to the next available tile
        if (!(std::find(walls.begin(), walls.end(), level[futureEnemyTile]) != walls.end()))
        {
            enemy.getSprite().setPosition(futureEnemyPos);
        }
    }
}

void Math::CorrectRectCollision(sf::FloatRect& rect1, sf::FloatRect& rect2)
{
    float overlapX = rect1.left + rect1.width - rect2.left;
    float overlapY = rect1.top + rect1.height - rect2.top;

    if (std::abs(overlapX) < std::abs(overlapY))
    {
        // Horizontal overlap is smaller, move horizontally
        if (overlapX > 0)
            rect1.left -= overlapX;
        else
            rect1.left += overlapX;
    }
    else
    {
        // Vertical overlap is smaller, move vertically
        if (overlapY > 0)
            rect1.top -= overlapY;
        else
            rect1.top += overlapY;
    }
}

