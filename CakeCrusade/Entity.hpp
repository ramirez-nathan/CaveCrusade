#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
    float health;
    float damage;
    float defense;

public:
    Entity(float h, float d, float def);
  

    // Getters
    float getHealth() const;
    float getDamage() const;
    float getDefense() const;


    // Setters
    void setHealth(float& h);
    void setDamage(float& d);
    void setDefense(float& def);


    // Functions
    void attackMove();

};