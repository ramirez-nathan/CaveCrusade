#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.hpp"

using namespace std;

class Soldier : public Entity
{
private:
	sf::Texture texture;
	sf::Vector2f direction;


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
	void Update(double deltaTime, Entity& player, int level[]);
	void Draw(sf::RenderWindow& window);

};