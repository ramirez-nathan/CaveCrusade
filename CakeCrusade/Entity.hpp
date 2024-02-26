#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <ostream>

class Entity {
private:
    

protected:
    float health;
    float damage;
    float defense;
    sf::Sprite sprite;
    sf::Texture texture;

    // size vector, width and height, gets set in initialize function
    sf::Vector2i size;

    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    

public:
    Entity(float h, float dmg, float def);
    virtual ~Entity() = default;
  

    // Getters
    float getHealth() const;
    float getDamage() const;
    float getDefense() const;
    int getSizeX() const { return size.x; } 
    int getSizeY() const { return size.y; } 
    sf::Sprite& getSprite() { return sprite; }


    // Setters
    void ChangeHealth(float hp) { health += hp; } 
    void setHealth(float& h);
    void setDamage(float& dmg);
    void setDefense(float& def);

    //void setSize(sf::Vector2i newSize) { size = newSize; } // dont think I need this

    //TODO: Virtual Function for Load()

    // Functions
    virtual void attackMove() = 0;
    bool loadTexture(const std::string& texturePath);

    // Draw the entity to the render window
    //void draw(sf::RenderWindow& window) const;

};