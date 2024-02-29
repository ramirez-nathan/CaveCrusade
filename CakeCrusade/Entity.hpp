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
    sf::Vector2i size;

    sf::Vector2f direction;

    sf::RectangleShape boundingRectangle;
    int SpriteX = 0;
    int SpriteY = 0;
    
    

public:
    // Our constructor, we define our health, damage, and defense values here
    Entity(float h, float dmg, float def, float spd);
    // Our destructor
    virtual ~Entity() = default;
    // Sets up the hitboxes for our entities
    virtual void Initialize();
    // void Load();
    // Loads in the sprite to be displayed
    void Load();
    virtual void Update(double deltaTime, const sf::Vector2f& target, int level[]);
    virtual void Draw(sf::RenderWindow& window);

  

    // Getters
    float getHealth() const { return health; }
    float getDamage() const { return damage; }
    float getDefense() const { return defense; }
    int getSizeX() const { return size.x; } 
    int getSizeY() const { return size.y; } 
    sf::Sprite& getSprite() { return sprite; }


    // Setters
    void ChangeHealth(float hp) { health += hp; } 
    void setHealth(float& h) { this->health = h; }
    void setDamage(float& dmg) { this->damage = dmg; }
    void setDefense(float& def) { this->defense = def; }

    //void setSize(sf::Vector2i newSize) { size = newSize; } // dont think I need this

    //TODO: Virtual Function for Load()

    // Functions
    virtual void attackMove() = 0;
    bool loadTexture(const std::string& texturePath);
    void changePosition(float x, float y);


    // Draw the entity to the render window
    //void draw(sf::RenderWindow& window) const;

};