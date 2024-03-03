#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"

using namespace std;

class Player : public Entity
{
private:
	vector<Arrow> Arrows;

	float MaxFireRate;
	double FireRateTimer;

	int SpriteX = 0;
	int SpriteY = 0;

public:
	Player(float h, float dmg, float def, float spd);
	~Player();

	void initialize() override;
	void load() override; 
	void update(const double deltaTime, Entity& soldier, Entity& skeleton, Entity& slime, sf::Vector2f& mousePosition, int level[]); 
	void drawPlayer(sf::RenderWindow& window);
	virtual void attackMove() override;
	void handleArrow(const double deltaTime, Entity& soldier, Entity& skeleton, Entity& slime, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void handleMovement(const double deltaTime, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
};