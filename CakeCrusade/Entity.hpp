#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
    float health;
    float damage;

public:
    Entity(float h, float d) 
       : health(h), damage(d) 
    {
    }

    // Getters
    float getHealth() const { return health; }
    float getDamage() const { return damage; }

    // Setters
    void setHealth(float& h) { health = h; }
    void setDamage(float& d) { damage = d; }
};