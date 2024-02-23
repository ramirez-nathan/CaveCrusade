#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
    float health;
    float damage;

    // size vector, width and height, gets set in initialize function
    sf::Vector2i size;

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

    // Setters
    void setHealth(float& h) { health = h; }
    void setDamage(float& d) { damage = d; }
    void ChangeHealth(float hp) { health += hp;  }

    void setSize(sf::Vector2i newSize) { size = newSize; }

    //TODO: Virtual Function for Load()
};