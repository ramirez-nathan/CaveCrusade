#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Math.hpp"
#include <vector>
#include <ostream>

using namespace std;

class Entity {
protected:
    // Every entity should have health, damage, defense, speed, a sprite, texture, and a hitbox
    float health;
    float damage;
    float defense;
    float entitySpeed;
    sf::Sprite sprite;
    sf::Texture texture;

    // size vector, width and height, gets set in initialize function
    sf::Vector2i Size;

    sf::Vector2f direction;

    sf::RectangleShape boundingRectangle;
    int SpriteX = 0;
    int SpriteY = 0;
    
    sf::RectangleShape BoundingRectangle;
    vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    // new code?

    

public:
    // Our constructor, we define our health, damage, and defense values here
    Entity(float h, float dmg, float def, float spd);
    // Our destructor
    virtual ~Entity() = default;
  

    // void Load();
    // Loads in the sprite to be displayed
    virtual void Load();
    virtual void Update(double deltaTime, const sf::Vector2f& target, int level[]);
    virtual void Draw(sf::RenderWindow& window);

  

    // Getters
    float getHealth() const { return Health; }
    float getDamage() const { return Damage; }
    float getDefense() const { return Defense; }
    int getSizeX() const { return Size.x; }
    int getSizeY() const { return Size.y; }
    sf::Sprite& getSprite() { return Sprite; }


    // Setters
    void changeHealth(float hp) { Health += hp; }
    void setHealth(float& h) { this->Health = h; }
    void setDamage(float& dmg) { this->Damage = dmg; }
    void setDefense(float& def) { this->Defense = def; }


    //TODO: Virtual Function for Load()

    // Functions
    virtual void attackMove() = 0;
    bool loadTexture(const std::string& texturePath);

    void loadTexture(const std::string& texturePath);
    //virtual void draw(sf::RenderWindow& window) = 0;

};