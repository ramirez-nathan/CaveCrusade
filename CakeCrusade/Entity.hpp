#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
protected:
    float health;
    float damage;
    float defense;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Entity(float h, float dmg, float def);
    virtual ~Entity() = default;
  

    // Getters
    float getHealth() const;
    float getDamage() const;
    float getDefense() const;


    // Setters
    void setHealth(float& h);
    void setDamage(float& dmg);
    void setDefense(float& def);


    // Functions
    virtual void attackMove() = 0;
    bool loadTexture(const std::string& texturePath);

    // Set the position of the entity
    void setPosition(const sf::Vector2f& position);

    // Get the current position of the entity
    const sf::Vector2f& getPosition() const;

    // Draw the entity to the render window
    void draw(sf::RenderWindow& window) const;

};