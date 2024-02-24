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

    // size vector, width and height, gets set in initialize function
    sf::Vector2i size;

    sf::Sprite sprite;
    sf::RectangleShape boundingRectangle;
    vector<int> walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };

public:
    Entity(float h, float d) 
       : health(h), damage(d) 
    { 
    } 

    // Getters
    float getHealth() const { return health; } 
    float getDamage() const { return damage; } 
    int getSizeX() const { return size.x; } 
    int getSizeY() const { return size.y; } 
    sf::Sprite& getSprite() { return sprite; }

    // Setters
    void setHealth(float& h) { health = h; } 
    void setDamage(float& d) { damage = d; } 
    void ChangeHealth(float hp) { health += hp; } 

    //void setSize(sf::Vector2i newSize) { size = newSize; } // dont think I need this

    //TODO: Virtual Function for Load()
};