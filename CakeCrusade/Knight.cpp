#include "Knight.hpp"
#include <iostream>


Knight::Knight(float h, float dmg, float def, float spd, float rng) : Soldier(h, dmg, def, spd, rng), MaxSwingRate(1100), SwingRateTimer(0)
{
}

void Knight::load()
{
    // Load the idle texture
    if (!Texture.loadFromFile("assets/enemies/knight/textures/evil_soldier_idle.png")) {
        cout << "Cannot load idle texture" << endl;
    }
    else {
        // If loading succeeds, set the sprite to use the idle texture initially
        Sprite.setTexture(Texture);
    }

    // Load the attacking texture
    if (!AttackTexture.loadFromFile("assets/enemies/knight/textures/evil_soldier_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }

    if (!WalkingTexture.loadFromFile("assets/enemies/knight/textures/evil_soldier_walking.png"))
        std::cerr << "Failed to load texture from " << "assets/enemies/evil_soldier/textures/evil_soldier_walking.png" << std::endl;

    // Call the load method of the base class if necessary
    SpriteX = 0;
    SpriteY = 0;
    // grab the idle texture image from spritesheet
    Sprite.setTextureRect(sf::IntRect(SpriteX * getSizeX(), SpriteY * getSizeY(), getSizeX(), getSizeY()));
    // set origin at middle of sprite
    Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f + 14);
    // change sprite scale
    Sprite.scale(sf::Vector2f(4.0f, 4.0f));
    // wrap the hitbox around the soldier
    BoundingRectangle.setSize(sf::Vector2f(Size.x * (Sprite.getScale().x - 2.1), Size.y * (Sprite.getScale().y - 1.35)));
    // set hitbox origin to middle
    BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f + 34);
}

void Knight::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) {
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
                //cout << "Sprite X value is " << SpriteX << endl;
                //cout << "Sprite Y value is " << SpriteX << endl;
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

void Knight::handleSword(const double deltaTime, Entity& player, sf::Vector2f& playerPosition, int level[], vector<int>& walls)
{
    SwingRateTimer += deltaTime;
    swingingAnimation();
    //cout << (SwingRateTimer >= MaxSwingRate && canAttack(playerPosition)) << endl;
    if (SwingRateTimer >= MaxSwingRate && canAttack(playerPosition))
    {
        IsAttacking = true;
        if (IsAttacking && (AttackingSpriteX == 2 || AttackingSpriteX == 3)) {
            if (player.getGoldHalfHearts() > 0) {

                player.changeGoldHalfHearts(-2);

                cout << "You were slashed by a soldier! Your amount of gold half hearts is: " << player.getGoldHalfHearts() << endl;

            }
            else if (player.getHalfHearts() > 0) {

                player.changeHalfHearts(-2);

                cout << "You were slashed by a soldier! Your amount of half hearts is: " << player.getHalfHearts() << endl;

            }
            SwingRateTimer = 0;
        }
    }
}



bool Knight::canAttack(const sf::Vector2f& playerPosition)
{
    // Calculate the distance between the enemy and the player
    float Dx = Sprite.getPosition().x - playerPosition.x;
    float Dy = Sprite.getPosition().y - playerPosition.y;


    // Check if the enemy is within the cone angle in each direction
    if ((Direction.x == 0.f && Direction.y > 0.f) || (Direction.x != 0.f && Direction.y > 0.5f)) { // Looking Down, Looking Down Diagonally
        AttackingSpriteY = 0;
        if ((Dx >= -70 && Dx <= 70) && (Dy >= -110 && Dy <= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x > 0.f && Direction.y == 0.f) || (Direction.x > 0.f && (-0.50f <= Direction.y && Direction.y <= 0.5f))) { // Looking Right, Looking Right Diagonally
        AttackingSpriteY = 2;
        if ((Dy <= 70 && Dy >= -70) && (Dx >= -90 && Dx <= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x < 0.f && Direction.y == 0.f) || (Direction.x < 0.f && (-0.5f <= Direction.y && Direction.y <= 0.5f))) { // Looking Left, Looking Left Diagonally
        AttackingSpriteY = 3;
        if ((Dy <= 70 && Dy >= -70) && (Dx <= 90 && Dx >= 0)) {
            return true;
        }
        return false;
    }
    else if ((Direction.x == 0.f && Direction.y < 0.f) || (Direction.x != 0.f && Direction.y < -0.5f)) { // Looking Up, Looking Up Diagonally
        AttackingSpriteY = 1;
        if ((Dx >= -70 && Dx <= 70) && (Dy <= 110 && Dy >= 0)) {
            return true;
        }
        return false;
    }
}

void Knight::swingingAnimation() {
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
        if (AttackClock.getElapsedTime().asSeconds() > 0.20f) {
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

bool Knight::isAggressive(const sf::Vector2f& playerPosition) const
{
    // Get the enemy's current position from its sprite
    sf::Vector2f enemyPosition = Sprite.getPosition();

    // Calculate the distance between the enemy and the player
    float dx = playerPosition.x - enemyPosition.x;
    float dy = playerPosition.y - enemyPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Check if the distance is within the specified attack range
    return distance <= this->aggressiveRange;
}

void Knight::makeAggressive(const sf::Vector2f& playerPosition)
{
    sf::Vector2f enemyPosition = Sprite.getPosition();
    float deltaX = playerPosition.x - enemyPosition.x;
    float deltaY = playerPosition.y - enemyPosition.y;
    const sf::IntRect rectDownA(0 * SpriteWidth, 0 * SpriteHeight, SpriteWidth, SpriteHeight); // Facing down aggro
    const sf::IntRect rectUpA(0 * SpriteWidth, 1 * SpriteHeight, SpriteWidth, SpriteHeight); // Facing up aggro
    const sf::IntRect rectRightA(0 * SpriteWidth, 2 * SpriteHeight, SpriteWidth, SpriteHeight); // Facing right aggro
    const sf::IntRect rectLeftA(0 * SpriteWidth, 2 * SpriteHeight, SpriteWidth, SpriteHeight); // Facing left aggro


    if (isAggressive(playerPosition)) {
        //cout << "Enemies are aggressive" << endl;
        Sprite.setTexture(AttackTexture);
        // Player is to the right
        if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectRightA);
        }
        // Player is to the left 
        else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {
            Sprite.setTextureRect(rectLeftA);
        }
        // Player is below
        else if (deltaY > 0) {
            Sprite.setTextureRect(rectDownA);
        }
        // Player is above
        else {
            Sprite.setTextureRect(rectUpA);
        }
    }
}
