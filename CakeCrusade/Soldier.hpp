#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"
#include "Math.hpp"

using namespace std;

class Soldier : public Entity
{
protected:
	sf::Vector2f direction;


	int SpriteX = 0;
	int SpriteY = 0;

	float soldierSpeed;
	

public:
	Soldier(float h, float dmg, float def);
	~Soldier();


	void Initialize();
	void Load();
	void Update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]);
	void Draw(sf::RenderWindow& window);
	virtual void attackMove() override;

};