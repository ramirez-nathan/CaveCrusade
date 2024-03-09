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
    float Damage;
    float Defense;
    float EntitySpeed;
    sf::Sprite Sprite;
    sf::Texture Texture;

    // size vector, width and height, gets set in initialize function
    sf::Vector2i Size;

    sf::Vector2f Direction;
    
    float frameAnimationPause = 250.f; // quarter of a second
    int SpriteX = 0;
    int SpriteY = 0;
    
    sf::RectangleShape BoundingRectangle;
    vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46, 47 };

    
public:
    // Our constructor, we define our health, damage, and defense values here
    Entity(float h, float dmg, float def, float spd);
    // Our destructor
    virtual ~Entity() = default;
    

    // void Load();
    // Loads in the sprite to be displayed
    virtual void load();
    virtual void initialize();
    virtual void handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls);
    virtual void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]);
    virtual void draw(sf::RenderWindow& window);


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

};