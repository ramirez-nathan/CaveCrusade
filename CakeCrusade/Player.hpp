#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"

using namespace std;

class Player : public Entity
{
private:
	vector<Arrow> arrows;

	float maxFireRate;
	double fireRateTimer;

	float playerSpeed;

	int SpriteX = 0;
	int SpriteY = 0;

public:
	Player(float h, float dmg, float def);
	~Player();
	
	void Initialize();
	void Load(); 
	void Update(double deltaTime, Entity& enemy, sf::Vector2f& mousePosition, int level[]); 
	void Draw(sf::RenderWindow& window);
	virtual void attackMove() override;
	void HandleMovement(double deltaTime, sf::Vector2f& movement, int& spriteX, int& spriteY, int direction, int level[], vector<int>& walls);
};