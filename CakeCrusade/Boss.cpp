#include "Boss.hpp"
#include <iostream>

Boss::Boss(float h, float dmg, float def, float spd)
	:Enemy(h,dmg,def,spd) {}


void Boss::load() {
	//loadTexture("assets/enemies/gingerbread_boss.png"); //will be able to load this once we have the image decided on
	loadTexture("assets/enemies/Pink_Monster.png"); //image that will be changed later
	SpriteX = 0;
	SpriteY = 0;
	// change sprite scale
	Sprite.scale(sf::Vector2f(4, 4));
	// set origin at middle of sprite
	Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f);
	// wrap the hitbox around the boss
	BoundingRectangle.setSize(sf::Vector2f(Size.y * Sprite.getScale().y, Size.x * Sprite.getScale().x));
	// set hitbox origin to middle
	BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f);
}

void Boss::initialize() {
	BoundingRectangle.setFillColor(sf::Color::Transparent);
	BoundingRectangle.setOutlineColor(sf::Color::Red);
	BoundingRectangle.setOutlineThickness(1);

	Size = sf::Vector2i(32, 16);
}

void Boss::handleMovement(double deltaTime, sf::Vector2f& direction, int& spriteX, int& spriteY, int level[], vector<int>& walls) {
	sf::Vector2f Position = Sprite.getPosition();

	static double elapsedTime = 0.0;
	elapsedTime += deltaTime;
	
	if (elapsedTime >= 2000.0) {
		elapsedTime = 0.0;
		float posX = static_cast<float>(rand() % 1200);
		float posY = static_cast<float>(rand() % 500);

		sf::Vector2f NewPosition(posX, posY);


		int FuturePos = floor(NewPosition.y / 64) * 22 + floor(NewPosition.x / 64);
		if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
			Sprite.setPosition(NewPosition);
		}
	}
}

void Boss::handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls) {
	
}

void Boss::transparency(double deltaTime) {
	static double currentVisibility = 255.0f;
	const double targetVisibility = 0.0f;
	const double fadeSpeed = 40.0f;

	if (currentVisibility > targetVisibility) {
		currentVisibility -= fadeSpeed * deltaTime;
		if (currentVisibility <= targetVisibility) {
			currentVisibility = targetVisibility;
		}
	}

	sf::Color color = Sprite.getColor();
	Sprite.setColor(color);
}









