#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
    float health;
    float damage;
    float defense;

public:
    Entity(float h, float dmg, float def);
  

    // Getters
    float getHealth() const;
    float getDamage() const;
    float getDefense() const;


    // Setters
    void setHealth(float& h);
    void setDamage(float& dmg);
    void setDefense(float& def);


    // Functions
    virtual void attackMove();

};