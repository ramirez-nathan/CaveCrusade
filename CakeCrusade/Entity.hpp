#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Math.hpp"
#include <vector>
#include <ostream>
#include <memory>

using namespace std;

class Entity {
protected:
    // Every entity should have health, damage, defense, speed, a sprite, texture, and a hitbox
    float Health;
    float MaxHealth;
    float Damage;
    float Defense;
    float EntitySpeed;

    sf::Sprite Sprite;
    sf::Texture Texture;

    sf::Clock WalkingClock;
    sf::Clock IdleClock;


    bool IsMoving = false;

    bool WalkingAnimationComplete = true;

    bool UpdateHandlingComplete = true;

    int EntityDirection = 0;
    // size vector, width and height, gets set in initialize function
    sf::Vector2i Size;

    sf::Vector2f Direction;
    
    int SpriteX = 0;
    int SpriteY = 0;

    int AttackingSpriteX = -1;
    int AttackingSpriteY = 0;

    int IdleSpriteX = 0;
    int IdleSpriteY = 0;

    int ShootingSpriteX = 1;
    int ShootingSpriteY = 0;

    int WalkingSpriteX = 0;
    int WalkingSpriteY = 0;

    
    sf::RectangleShape BoundingRectangle;
    vector<int> ArrowWalls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46, 47 };
    vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46, 47, 48 };
    const float knockbackDistance = 50.0f; // Distance to knock back

    

public:
    // Our constructor, we define our health, damage, and defense values here
    Entity(float h, float dmg, float def, float spd);
    // Our destructor
    virtual ~Entity() = default;
    

    // void Load();
    // Loads in the sprite to be displayed
    virtual void load();
    virtual void initialize();
    virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int entityDirection, int level[], vector<int>& walls);
    virtual void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]);
    virtual void draw(sf::RenderWindow& window);
    void getKnockedBack(const sf::Vector2f& attackerPosition, int level[], vector<int>& walls);
    bool isAttacked() const;


    // Getters
    float getHealth() const { return Health; }
    float getDamage() const { return Damage; }
    float getDefense() const { return Defense; }
    int getSizeX() const { return Size.x; }
    int getSizeY() const { return Size.y; }
    sf::Sprite& getSprite() { return Sprite; }
    sf::RectangleShape& getHitBox() { return BoundingRectangle; }


    // Setters
    void changeHealth(float hp) { Health += hp; }
    void changeDefense(float def) { Defense += def; }
    void setHealth(float& h) { this->Health = h; }
    void setDamage(float& dmg) { this->Damage = dmg; }
    void setDefense(float& def) { this->Defense = def; }


    //TODO: Virtual Function for Load()
    virtual void attackMove(const double deltaTime, Entity&) = 0;
    // Functions
    void changePosition(float x, float y);
    void loadTexture(const std::string& texturePath);
    //virtual void draw(sf::RenderWindow& window) = 0;

    virtual void walkingAnimation(int direction);

    Entity() = default;
};