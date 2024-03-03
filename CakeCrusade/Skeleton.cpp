#include "Skeleton.hpp"

Skeleton::Skeleton(float h, float dmg, float def, float spd)
	: Entity(h, dmg, def, spd), MaxFireRate(1100), FireRateTimer(0) {}


void Skeleton::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) // No move!
{ 
    // Additional code for WASD movements
    if ((direction.x == 0.f && direction.y > 0.f) || (direction.x != 0.f && direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        spriteX = 0;
        spriteY = 0;

    }
    else if ((direction.x > 0.f && direction.y == 0.f) || (direction.x > 0.f && (-0.50f <= direction.y && direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        spriteX = 0;
        spriteY = 2; // CHANGE WHEN SPRITESHEET GETS UPDATED

    }
    else if ((direction.x < 0.f && direction.y == 0.f) || (direction.x < 0.f && (-0.5f <= direction.y && direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 2;

    }
    else if ((direction.x == 0.f && direction.y < 0.f) || (direction.x != 0.f && direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        spriteX = 0;
        spriteY = 1;

    }

    Sprite.setTextureRect(sf::IntRect(spriteX * getSizeX(), spriteY * getSizeY(), getSizeX(), getSizeY()));
   
}

// takes parameters : delta time, player position, level
void Skeleton::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[])
{
    if (Health > 0)
    {
        Direction = Math::normalizeVector(target - Sprite.getPosition());
        handleMovement(deltaTime, Direction, SpriteX, SpriteY, level, Walls);
        handleArrow(deltaTime, player, target, FireRateTimer, MaxFireRate, level, Walls);

        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Skeleton::handleArrow(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls)
{
    FireRateTimer += deltaTime;

    if (FireRateTimer >= MaxFireRate)
    {
        Arrows.push_back(Arrow());
        int i = Arrows.size() - 1;
        Arrows[i].initialize(Sprite.getPosition(), target, 0.5f);
        FireRateTimer = 0;
    }

    for (size_t i = 0; i < Arrows.size(); i++)
    {
        if (Arrows[i].didArrowHitWall(deltaTime, walls, level))
        {
            Arrows.erase(Arrows.begin() + i);
        }
        else {
            Arrows[i].update(deltaTime);
            if (player.getHealth() > 0 && Arrows.size() > 0)
            {
                // implement this when collision is finished
                if (Math::didRectCollide(Arrows[i].getArrowGlobalBounds(), player.getHitBox().getGlobalBounds()))
                {
                    if (player.getDefense() > 0) {
                        player.changeDefense(-25);
                    }
                    else {
                        player.changeHealth(-25);
                    }
                    Arrows.erase(Arrows.begin() + i);
                    cout << "Player's health is: " << player.getHealth() << endl;
                    continue;
                }
            }
        }
    }
}

void Skeleton::draw(sf::RenderWindow& window) {
    if (Health > 0)
    {
        window.draw(Sprite);
        window.draw(BoundingRectangle);

        for (size_t i = 0; i < Arrows.size(); i++)
            Arrows[i].drawArrow(window);
    }
}

void Skeleton::attackMove() {
    cout << "Skeleton attack works!" << endl;
}