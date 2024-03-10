#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "memory"

using namespace std;

class Player : public Entity
{
private:
	vector<Arrow> Arrows;
	sf::Texture ShootingTexture;
	sf::Texture WalkingTexture;
	float MaxFireRate;
	double FireRateTimer;
	int Ammo = 20;

	
	bool ShootingArrow = false;
	bool ShootingAnimationComplete = true;
	bool FinishedAnimation = false;
	int PlayerDirection = 0;

	int ShootingSpriteX = 1; 
	int ShootingSpriteY = 0; 
	int ArrowSpriteX = 0; 
	int ArrowSpriteY = 0; 

public:
	Player(float h, float dmg, float def, float spd);
	~Player();

	void changeAmmo(int ammo) { Ammo += ammo; }
	void initialize() override;
	void load() override; 
	void playerUpdate(const double deltaTime, sf::Clock& idleAnimationClock, sf::Clock& shootingClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int level[]);
	void arrowShootAnimation(sf::Clock& shootingClock, sf::Vector2f direction);

	bool isTouchingDoor(int level[]);
	void drawPlayer(sf::RenderWindow& window);
	virtual void attackMove(const double deltaTime, Entity& enemy) override;
	void handleArrow(const double deltaTime, sf::Clock& shootingClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void handleMovement(const double deltaTime, bool& isMoving, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
};