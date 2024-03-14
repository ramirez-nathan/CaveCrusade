#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rock.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

using namespace std;

class RockHandler : public Enemy
{
private:
    vector<Rock> Rocks;
    float maxFireRate;
    double fireRateTimer;

public:
    RockHandler(float h, float dmg, float def, float spd);
    ~RockHandler() = default;
    virtual void initialize() override;
    virtual void load() override;
    void handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
    virtual void draw(sf::RenderWindow& window) override;
    virtual void update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]) override; 
};
