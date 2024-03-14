#include "Boss.hpp"
#include <iostream>

Boss::Boss(float h, float dmg, float def, float spd)
	:Enemy(h, dmg, def, spd), maxFireRate(1100.f), fireRateTimer(0) {}


void Boss::load() {
	loadTexture("assets/enemies/boss/pink_monster.png"); 
	SpriteX = 0;
	SpriteY = 0;
	// change sprite scale
	Sprite.scale(sf::Vector2f(4, 4));
	// set origin at middle of sprite
	Sprite.setOrigin(Sprite.getLocalBounds().width / 2.f, Sprite.getLocalBounds().height / 2.f);
	// wrap the hitbox around the boss
	BoundingRectangle.setSize(sf::Vector2f(Size.x * Sprite.getScale().y, Size.y * Sprite.getScale().x));
	// set hitbox origin to middle
	BoundingRectangle.setOrigin(BoundingRectangle.getSize().x / 2.f, BoundingRectangle.getSize().y / 2.f);
}

void Boss::initialize() {
	BoundingRectangle.setFillColor(sf::Color::Transparent);
	BoundingRectangle.setOutlineColor(sf::Color::Red);
	BoundingRectangle.setOutlineThickness(1);

	Size = sf::Vector2i(16, 32);
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


		int FuturePos = floor(NewPosition.x / 64) * 22 + floor(NewPosition.y / 64);
		if (!(std::find(walls.begin(), walls.end(), level[FuturePos]) != walls.end())) {
			Sprite.setPosition(NewPosition);
		}
	}
}

void Boss::handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls) {
	fireRateTimer += deltaTime;
	const float maxX = 1400.0f;

	if (fireRateTimer >= maxFireRate) {

		// Initial rock position
		static sf::Vector2f rockPosition(100.0f, 100.0f);

		sf::Vector2f shift(100.0f, 0.0f);

		Rocks.push_back(Rock());
		size_t i = Rocks.size() - 1;
		Rocks[i].initialize(rockPosition, target, 0.5f);

		// Update rock position for the next iteration
		rockPosition += shift;

		if (rockPosition.x > maxX) {
			rockPosition.x = 100.0f; // Reset to the initial position
		}

		// Reset fire rate timer
		fireRateTimer = 0;
	}

	for (size_t i = Rocks.size(); i > 0; i--)
	{
		if (Rocks[i - 1].didRockHitWall(deltaTime, walls, level))
		{
			// if an rock hits a wall, erase it from the vector
			Rocks.erase(Rocks.begin() + (i - 1));
			continue;
		}

		Rocks[i - 1].update(deltaTime);

		// check for collisions with the player
		if (player.getHealth() > 0) {
			if (Math::didRectCollide(Rocks[i - 1].getRockGlobalBounds(), player.getHitBox().getGlobalBounds()))
			{
				if (player.getDefense() > 0) {
					player.changeDefense(-25);
				}
				else {
					player.changeHealth(-25);
				}

				// erase the rock from the vector
				Rocks.erase(Rocks.begin() + (i - 1));
				cout << "You've been hit by a load of rocks!" << endl;
				cout << "Player's health is: " << player.getHealth() << endl;
			}
		}
	}
}

void Boss::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[]){
	if (Health > 270) {
		Direction = Math::normalizeVector(target - Sprite.getPosition());

		handleMovement(deltaTime, Direction, SpriteX, SpriteY, level, Walls);

		handleRocks(deltaTime, player, target, fireRateTimer, maxFireRate, level, Walls);

		BoundingRectangle.setPosition(Sprite.getPosition());
	}
	if (Health < 250) {
		transparency(deltaTime);
	}
}

void Boss::transparency(double deltaTime) {
	static double currentVisibility = 255.0f;
	const double targetVisibility = 150.0f;
	const double fadeSpeed = 0.5f;

	double timeTracker = 0.0;
	timeTracker += deltaTime;
	

	if (timeTracker >= deltaTime) {
		if (currentVisibility > targetVisibility) {
			currentVisibility -= fadeSpeed;

			sf::Color color = Sprite.getColor();
			color.a = static_cast<sf::Uint8>(currentVisibility);
			Sprite.setColor(color);

			if (currentVisibility <= targetVisibility) {
				currentVisibility = targetVisibility;
			}
		}
	}
}

void Boss::draw(sf::RenderWindow& window) {
	if (Health > 0)
	{
		window.draw(Sprite);
		window.draw(BoundingRectangle);

		for (size_t i = 0; i < Rocks.size(); i++)
			Rocks[i].drawRock(window);
	}
}









