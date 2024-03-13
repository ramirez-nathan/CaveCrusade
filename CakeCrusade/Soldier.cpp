#include "Soldier.hpp"
#include <iostream>

Soldier::Soldier(float h, float dmg, float def, float spd, float rng)
	: Enemy(h, dmg, def, spd), MaxSwingRate(500), SwingRateTimer(0)
{
}

void Soldier::load() {
    // Load the idle texture
    if (!Texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png")) {
        cout << "Cannot load idle texture" << endl;
    }
    else {
        // If loading succeeds, set the sprite to use the idle texture initially
        Sprite.setTexture(Texture);
    }

    // Load the attacking texture
    if (!AttackTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }

    if (!WalkingTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_walking.png"))
        std::cerr << "Failed to load texture from " << "assets/enemies/evil_soldier/textures/evil_soldier_walking.png" << std::endl;
    // Call the load method of the base class if necessary
    Entity::load();
}

void Soldier::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) {
    if (Health > 0)
    {
        sf::Vector2f playerDirection = player.getSprite().getPosition();
        UpdateHandlingComplete = false;

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
        if (Math::didRectCollide(BoundingRectangle.getGlobalBounds(), player.getHitBox().getGlobalBounds())) {
            CollisionFreeze.restart();
            IsFrozen = true;
            IsMoving = false;
        }
        if (CollisionFreeze.getElapsedTime().asSeconds() > 1.0f) {
            IsFrozen = false;
            IsMoving = true;
            handleSword(deltaTime, player, playerDirection, level, Walls);
        }
        handleMovement(deltaTime, Direction, SpriteX, SpriteY, EntityDirection, level, Walls);
        
        if (!IsMoving) {
            if (IdleClock.getElapsedTime().asSeconds() > 0.5f) {
                if (IdleSpriteX == 1)
                    IdleSpriteX = 0;
                else
                    IdleSpriteX += 1;
                IdleClock.restart();
            }
        }
        handleSword(deltaTime, player, playerDirection, level, Walls);
        
        UpdateHandlingComplete = true;
        //------------------------------------- LOAD CORRECT TEXTURE AND SPRITE INDEXES -----------------------------------
        if (UpdateHandlingComplete) {
            if (IsAttacking) {
                Sprite.setTexture(AttackTexture);
                SpriteX = AttackingSpriteX;
                SpriteY = AttackingSpriteY;
                Sprite.setTextureRect(sf::IntRect(SpriteX * (getSizeX() + 16), SpriteY * (getSizeY() + 16), (getSizeX() + 16), (getSizeY() + 16)));
            }
            else if (IsMoving) { // walking 
                Sprite.setTexture(WalkingTexture);
                SpriteX = WalkingSpriteX;
                SpriteY = WalkingSpriteY;
                Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
            }
            else { // if idle
                Sprite.setTexture(Texture);
                SpriteX = IdleSpriteX;
                Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
            }
        }
        IsMoving = false; // set it back to false after the movement to reset the bool for next loop
        //------------------------------------- LOAD CORRECT TEXTURE ----------------------------------- 
        BoundingRectangle.setPosition(Sprite.getPosition());
    }
}

void Soldier::handleSword(const double deltaTime, Entity& player, sf::Vector2f& playerPosition, int level[], vector<int>& walls) {
    SwingRateTimer += deltaTime;
    swingingAnimation();
    //cout << (SwingRateTimer >= MaxSwingRate && canAttack(playerPosition)) << endl;
    if (SwingRateTimer >= MaxSwingRate && canAttack(playerPosition))
    {
        IsAttacking = true;
        if (IsAttacking) {
            if (player.getGoldHalfHearts() > 0) {
                player.changeGoldHalfHearts(-1);
                
                cout << "You were slashed by a soldier! Your amount of gold half hearts is: " << player.getGoldHalfHearts() << endl;
            }
            else if (player.getHalfHearts() > 0) {
                player.changeHalfHearts(-1);

                cout << "You were slashed by a soldier! Your amount of half hearts is: " << player.getHalfHearts() << endl;
            }
            SwingRateTimer = 0;
        }
    }
}



bool Soldier::canAttack(const sf::Vector2f& playerPosition) 
{
    // Calculate the distance between the enemy and the player
    float Dx = Sprite.getPosition().x - playerPosition.x;
    float Dy = Sprite.getPosition().y - playerPosition.y;


    // Check if the enemy is within the cone angle in each direction
    if ((Direction.x == 0.f && Direction.y > 0.f) || (Direction.x != 0.f && Direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        AttackingSpriteY = 0;
        if ((Dx >= -60 && Dx <= 60) && (Dy >= -90 && Dy <= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x > 0.f && Direction.y == 0.f) || (Direction.x > 0.f && (-0.50f <= Direction.y && Direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        AttackingSpriteY = 3;
        if ((Dy <= 60 && Dy >= -60) && (Dx >= -90 && Dx <= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x < 0.f && Direction.y == 0.f) || (Direction.x < 0.f && (-0.5f <= Direction.y && Direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        AttackingSpriteY = 2;
        if ((Dy <= 60 && Dy >= -60) && (Dx <= 90 && Dx >= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x == 0.f && Direction.y < 0.f) || (Direction.x != 0.f && Direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        AttackingSpriteY = 1;
        if ((Dx >= -60 && Dx <= 60) && (Dy <= 90 && Dy >= 0)) {
            return true;
        }
        return false;
    }
}

void Soldier::swingingAnimation() {
    if (IsAttacking) {
        if (EntityDirection == 0) { // Looking Down, Looking Down Diagonally
            AttackingSpriteY = 0;
        }
        else if (EntityDirection == 3) { // Looking Right, Looking Right Diagonally
            AttackingSpriteY = 2;
        }
        else if (EntityDirection == 2) { // Looking Left, Looking Left Diagonally
            AttackingSpriteY = 3;
        }
        else if (EntityDirection == 1) { // Looking Up, Looking Up Diagonally
            AttackingSpriteY = 1;
        }
        AttackingAnimationComplete = false;
        if (AttackClock.getElapsedTime().asSeconds() > 0.10f) {
            if (AttackingSpriteX == 3) { // do nothing, just set shootingspritex up for the next time player shoots 
                AttackingAnimationComplete = true;
                IsAttacking = false;
                AttackingSpriteX = 0; // set it to next frame 
            }
            else {
                AttackingSpriteX++; // set shootingspritex to 0 for first frame
            }
            AttackClock.restart();
        }

    }
}

