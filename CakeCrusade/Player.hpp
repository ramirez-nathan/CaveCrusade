#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.hpp"
#include "Entity.hpp"
#include <vector>

using namespace std;

class Player : public Entity
{
private:
	sf::Texture texture;

	vector<Arrow> arrows;

	float maxFireRate;
	double fireRateTimer;

	float playerSpeed;

	int SpriteX = 0;
	int SpriteY = 0;

	// size vector, width and height, gets set in initialize function
	sf::Vector2i size;


public:
	sf::Sprite playerSprite;

public:
	Player(float h, float d);
	~Player();
	
	void Initialize();
	void Load();
	void Update(double deltaTime, Entity& enemy, sf::Vector2f& mousePosition, int level[]); // 
	void Draw(sf::RenderWindow& window);
};