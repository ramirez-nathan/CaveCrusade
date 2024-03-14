#include "Knight.hpp"
#include <iostream>

//Knight::Knight(float h, float dmg, float def, float spd, float rng) : Enemy(h, dmg, def, spd), MaxSwingRate(1100), SwingRateTimer(0) {
//
//}

void Knight::load()
{
    // Load the idle texture
    if (!Texture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png")) {
        cout << "Cannot load idle texture" << endl;
    }
    else {
        // If loading succeeds, set the sprite to use the idle texture initially
        Sprite.setTexture(Texture);
    }

    // Load the attacking texture
    if (!AttackTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_attacking.png")) {
        cout << "Cannot load attacking texture" << endl;
    }

    if (!WalkingTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_walking.png"))
        std::cerr << "Failed to load texture from " << "assets/enemies/evil_soldier/textures/evil_soldier_walking.png" << std::endl;
    // Call the load method of the base class if necessary
    Entity::load();
}
