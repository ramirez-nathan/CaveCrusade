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
	const string PlayerArrowPath = "assets/player/textures/new_arrow.png";
	sf::Texture ShootingTexture;
	sf::Texture WalkingTexture;
	sf::Texture AttackingTexture;
	float MaxFireRate;
	double FireRateTimer;
	float MaxSwingRate;
	double SwingRateTimer;

    sf::Clock PlayerIdleClock;
    sf::Clock PlayerShootClock;
    sf::Clock PlayerAttackingClock;
	

	bool IsAttacking = false;
	bool AttackingAnimationComplete = true;
	bool FinishedAttackingAnimation = false;

	//bool WalkingAnimationComplete = true;

	bool ShootingArrow = false;
	bool ShootingAnimationComplete = true;
	bool FinishedBowAnimation = false;

	

	int PlayerDirection = 0;

	

	//bool UpdateHandlingComplete = true;


protected:
	int Ammo = 10;
	
	//double GoldHalfHeartCount = 0;
	bool HasKey = true; // CHANGE WHEN KEY INTERACTABLE IS DONE

	bool HasBow = false;

public:
	Player(float h, float dmg, float def, float spd);
	~Player();
	double HeartContainerCount = 4;
	double GoldHeartContainerCount = 2;
	double DamageDone = 0;
	double HalfHeartCount = 8;
	double GoldHalfHeartCount = 0;

	// ------------------ GETTERS/SETTERS --------------------
	void changeAmmo(int ammo) { Ammo += ammo; }
	int getAmmo() { return Ammo; }

	int getDamageDone() { return DamageDone; }
	void setDamageDone(int damage) { DamageDone = damage; }

	bool getKeyState() { return HasKey; }
	bool getBowState() { return HasBow; }

	void setKeyState(bool state) { HasKey = state; }
	void setBowState(bool state) { HasBow = state; }

	virtual void setHeartContainer(int damage) override;
	virtual void setGoldContainer(int damage) override;

	virtual void changeHalfHearts(int damage) override;
	virtual void changeGoldHalfHearts(int damage) override;


	virtual double getGoldHeartContainer() override { return GoldHeartContainerCount; }
	virtual double getHeartContainer() override { return HeartContainerCount; }
		
	virtual double getGoldHalfHearts() override { return GoldHalfHeartCount; }
	virtual double getHalfHearts() override { return HalfHeartCount; }

	
	// ------------------ GETTERS/SETTERS --------------------

	// --------------------------------- CORE FUNCTIONS --------------------------------
	void initialize() override;
	void load() override; 
	void playerUpdate(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, int level[]);
	// --------------------------------- CORE FUNCTIONS --------------------------------
	
	//--------------------------- ANIMATIONS ---------------------------------
	void arrowShootAnimation(sf::Vector2f mouseDirection);
	void swingingAnimation(sf::Vector2f mouseDirection);
	virtual void walkingAnimation(int direction) override;
	//--------------------------- ANIMATIONS ---------------------------------
	
	//--------------------------- HELPER FUNCTIONS ---------------------------
	void handleArrow(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls);
	void handleSword(const double deltaTime, vector<unique_ptr<Enemy>>& enemies, sf::Vector2f& mousePosition, double& SwingRateTimer, const float& MaxSwingRate, int level[], vector<int>& walls);
	void handleMovement(const double deltaTime, bool& isMoving, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
	bool isTouchingDoor(int level[]);
	bool isTouchingStair(int level[]);
	bool isTouchingEntry(int level[]);
	void drawPlayer(sf::RenderWindow& window);
	virtual void attackMove(const double deltaTime, Entity& enemy) override;
	bool canAttack(const sf::Vector2f& enemyPosition, float attackRange, sf::Vector2f mouseDirection);
	//--------------------------- HELPER FUNCTIONS ---------------------------
};