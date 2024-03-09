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

	bool IsAttacking = false;

	bool IsMoving = false;

	bool ShootingArrow = false;
	bool ShootingAnimationComplete = true;
	bool FinishedBowAnimation = false;

	bool WalkingAnimationComplete = true;
	int PlayerDirection = 0;

	bool UpdateHandlingComplete = true;

	int IdleSpriteX = 0;
	int IdleSpriteY = 0;

	int ShootingSpriteX = 1; 
	int ShootingSpriteY = 0; 

	int WalkingSpriteX = 0;
	int WalkingSpriteY = 0;

protected:
	int Ammo;

public:
	Player(float h, float dmg, float def, float spd);
	~Player();
	// ------------------ GETTERS/SETTERS --------------------
	void changeAmmo(int ammo) { Ammo += ammo; }
	int getAmmo() { return Ammo; }
	// ------------------ GETTERS/SETTERS --------------------

	// --------------------------------- CORE FUNCTIONS --------------------------------
	void initialize() override;
	void load() override; 
	void playerUpdate(const double deltaTime, sf::Clock& idleAnimationClock, sf::Clock& shootingClock, sf::Clock& walkingClock, vector<unique_ptr<Enemy>>&enemies, sf::Vector2f& mousePosition, int level[]);
	// --------------------------------- CORE FUNCTIONS --------------------------------
	
	//--------------------------- ANIMATIONS ---------------------------------
	void arrowShootAnimation(sf::Clock& shootingClock, sf::Vector2f mouseDirection);
	void walkingAnimation(sf::Clock& walkingClock, int direction);
	//--------------------------- ANIMATIONS ---------------------------------
	
	//--------------------------- HELPER FUNCTIONS ---------------------------
	void handleArrow(const double deltaTime, sf::Clock& shootingClock, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void handleMovement(const double deltaTime, bool& isMoving, sf::Clock& walkingClock, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
	bool isTouchingDoor(int level[]);
	bool isTouchingStair(int level[]);
	void drawPlayer(sf::RenderWindow& window);
	virtual void attackMove(const double deltaTime, Entity& enemy) override;
	//--------------------------- HELPER FUNCTIONS ---------------------------
};