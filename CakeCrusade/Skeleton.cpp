#include "Skeleton.hpp"

Skeleton::Skeleton(float h, float dmg, float def, float spd)
	: Enemy(h, dmg, def, spd), MaxFireRate(1800.f), FireRateTimer(0) {}

void Skeleton::load()
{
    // Load the idle texture
    if (!Texture.loadFromFile("assets/enemies/skelly/idle/skull_idle.png")) {
        cout << "Cannot load idle texture" << endl;
    }
    else {
        // If loading succeeds, set the sprite to use the idle texture initially
        Sprite.setTexture(Texture);
    }

    // Load the attacking texture
    if (!AttackTexture.loadFromFile("assets/enemies/skelly/attacking/skull_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }
    Entity::load();
}

void Skeleton::handleSkeletonMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) // No move!
{ 
    // Additional code for WASD movements
    if ((direction.x == 0.f && direction.y > 0.f) || (direction.x != 0.f && direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        spriteX = 0;
        spriteY = 0;

    }
    else if ((direction.x > 0.f && direction.y == 0.f) || (direction.x > 0.f && (-0.50f <= direction.y && direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        spriteX = 0;
        spriteY = 2; 

    }
    else if ((direction.x < 0.f && direction.y == 0.f) || (direction.x < 0.f && (-0.5f <= direction.y && direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        spriteX = 0;
        spriteY = 3;

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

        if ((Direction.x == 0.f && Direction.y > 0.f) || (Direction.x != 0.f && Direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
            EntityDirection = 0;
        }
        else if ((Direction.x > 0.f && Direction.y == 0.f) || (Direction.x > 0.f && (-0.50f <= Direction.y && Direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
            EntityDirection = 3;

        }
        else if ((Direction.x < 0.f && Direction.y == 0.f) || (Direction.x < 0.f && (-0.5f <= Direction.y && Direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
            EntityDirection = 2;

        }
        else if ((Direction.x == 0.f && Direction.y < 0.f) || (Direction.x != 0.f && Direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
            EntityDirection = 1;
        }

        handleSkeletonMovement(deltaTime, Direction, SpriteX, SpriteY, level, Walls);

        if (!IsMoving) {
            if (IdleClock.getElapsedTime().asSeconds() > 0.5f) {
                if (IdleSpriteX == 1)
                    IdleSpriteX = 0;
                else
                    IdleSpriteX += 1;
                IdleClock.restart();
            }
        }

        handleArrow(deltaTime, player, target, FireRateTimer, MaxFireRate, level, Walls);

        UpdateHandlingComplete = true;
        //------------------------------------- LOAD CORRECT TEXTURE AND SPRITE INDEXES -----------------------------------
        if (UpdateHandlingComplete) {
            if (ShootingArrow) {
                Sprite.setTexture(AttackTexture);
                SpriteX = ShootingSpriteX;
                SpriteY = ShootingSpriteY;

                //cout << "Sprite X value is " << SpriteX << endl;
                //cout << "Sprite Y value is " << SpriteX << endl;

                //SpriteX = 1;
                //SpriteY = 0;

                
                Sprite.setTextureRect(sf::IntRect(SpriteX * (getSizeX()), SpriteY * (getSizeY()), (getSizeX()), (getSizeY())));
            }
            else { // if idle
                Sprite.setTexture(Texture);
                SpriteX = IdleSpriteX;
                Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
            }
        }

        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Skeleton::handleArrow(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls)
{
    FireRateTimer += deltaTime;
    // attackAnimation(player.getSprite().getPosition());

    if (FireRateTimer >= MaxFireRate)
    {
        ShootingArrow = true;
        attackAnimation(player.getSprite().getPosition());
        if (ShootingAnimationComplete) {
            SkellyArrows.push_back(Arrow());
            int i = SkellyArrows.size() - 1;
            SkellyArrows[i].initialize(Sprite.getPosition(), target, 0.5f, SkeletonArrowPath);
            FireRateTimer = 0;
        }
       
        
    }
    else {
        ShootingArrow = false;
    }

    // iterate through the arrows in reverse order
    for (size_t i = SkellyArrows.size(); i > 0; i--)
    {
        if (SkellyArrows[i - 1].didArrowHitWall(deltaTime, ArrowWalls, level))
        {
            // if an arrow hits a wall, erase it from the vector
            SkellyArrows.erase(SkellyArrows.begin() + (i - 1));
            continue;
        }

        SkellyArrows[i - 1].update(deltaTime);

        // check for collisions with the player
        if (player.getHealth() > 0) {
            if (Math::didRectCollide(SkellyArrows[i - 1].getArrowGlobalBounds(), player.getHitBox().getGlobalBounds()))
            {
                if (player.getGoldHalfHearts() > 0) {
                    player.changeGoldHalfHearts(-1);
                    cout << "You've been hit by an arrow!" << endl;
                   
                }
                else {
                    player.changeHalfHearts(-1);
                    cout << "You've been hit by an arrow!" << endl;
                    
                }

                // erase the arrow from the vector
                SkellyArrows.erase(SkellyArrows.begin() + (i - 1));
                
                cout << "Player's half hearts is: " << player.getHalfHearts() << ", gold half hearts is: " << player.getGoldHalfHearts() << endl;
            }
        }
    }
}

void Skeleton::draw(sf::RenderWindow& window) {
    if (Health > 0)
    {
        window.draw(Sprite);
        window.draw(BoundingRectangle);

        for (size_t i = 0; i < SkellyArrows.size(); i++)
            SkellyArrows[i].drawArrow(window);
    }
}

void Skeleton::attackAnimation(const sf::Vector2f& playerPosition)
{
    //cout << "Skeleton draws it bow" << endl;
    if (ShootingArrow) {
        if (EntityDirection == 0) { // Looking Down, Looking Down Diagonally
            ShootingSpriteY = 0;
            //cout << "ShootingSpriteY set to " << ShootingSpriteY << endl;
        }
        else if (EntityDirection == 3) { // Looking Right, Looking Right Diagonally
            ShootingSpriteY = 3;
            //cout << "ShootingSpriteY set to " << ShootingSpriteY << endl;
        }
        else if (EntityDirection == 2) { // Looking Left, Looking Left Diagonally
            ShootingSpriteY = 2;
            //cout << "ShootingSpriteY set to " << ShootingSpriteY << endl;
        }
        else if (EntityDirection == 1) { // Looking Up, Looking Up Diagonally
            ShootingSpriteY = 1;
            //cout << "ShootingSpriteY set to " << ShootingSpriteY << endl;
        }
        ShootingAnimationComplete = false;
        if (AttackClock.getElapsedTime().asSeconds() > 0.25f) {
            if (FinishedBowAnimation) {
                ShootingAnimationComplete = true;
                ShootingArrow = false;
                FinishedBowAnimation = false;
            }
            else if (ShootingSpriteX == 0) { // do nothing, just set shootingspritex up for the next time player shoots 
                FinishedBowAnimation = true;
                ShootingSpriteX = 1; // set it to next frame 
            }
            else {
                ShootingSpriteX--; // set shootingspritex to 0 for first frame
            }
            AttackClock.restart(); // restart so that we can check if a quarter second passed again in the next loop or so
        }
        }
    }


