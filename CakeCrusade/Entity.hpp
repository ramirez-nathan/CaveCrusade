#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <ostream>

using namespace std;

class Entity {
protected:
    float Health;
    float Damage;
    float Defense;
    sf::Sprite Sprite;
    sf::Texture Texture;

    // size vector, width and height, gets set in initialize function
    sf::Vector2i Size;

    sf::RectangleShape BoundingRectangle;
    vector<int> Walls{ 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
    // new code?


public:
    Entity(float h, float dmg, float def);
    virtual ~Entity() = default;


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
    void loadTexture(const std::string& texturePath);

    // Draw the entity to the render window
    //virtual void draw(sf::RenderWindow& window) = 0;

};