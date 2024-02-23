#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

using namespace std;

class Soldier : public Entity
{
private:
	sf::Texture texture;

	int SpriteX = 0;
	int SpriteY = 0;

	float soldierSpeed;

public:
	//sf::Sprite soldierSprite;
public:
	Soldier(float h, float d);
	~Soldier();

	 
	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

};