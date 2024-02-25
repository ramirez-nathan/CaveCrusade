#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

using namespace std;

class Soldier : public Entity
{
private:
	sf::Texture texture;

	int XIndex = 0;
	int YIndex = 0;

public:
	sf::Sprite soldierSprite;
	sf::Vector2i size;
public:
	Soldier(float h, float dmg, float def);
	~Soldier();

	void ChangeHealth(float hp);

	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
	virtual void attackMove() override;

};