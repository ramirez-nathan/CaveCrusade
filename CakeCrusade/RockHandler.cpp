#include "RockHandler.hpp"
#include <iostream>

RockHandler::RockHandler(float h, float dmg, float def, float spd)
	:Enemy(h, dmg, def, spd), maxFireRate(2000.f), fireRateTimer(0) {}


void RockHandler::load() {
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

void RockHandler::initialize() {
	BoundingRectangle.setFillColor(sf::Color::Transparent);
	BoundingRectangle.setOutlineColor(sf::Color::Red);
	BoundingRectangle.setOutlineThickness(1);

	Size = sf::Vector2i(16, 32);
}


void RockHandler::handleRocks(const double deltaTime, Entity& player, const sf::Vector2f& target, double& fireRateTimer, const float& maxFireRate, int level[], vector<int>& walls) {
	fireRateTimer += deltaTime;
	const float maxX = 1400.0f;

	if (fireRateTimer >= maxFireRate) {

		// Initial rock position
		static sf::Vector2f rockPosition(700.0f, 50.0f);

		sf::Vector2f shift(100.0f, 0.0f);

		Rocks.push_back(Rock());
		size_t i = Rocks.size() - 1;
		Rocks[i].initialize(rockPosition, target, 0.3f);

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
		if (Rocks[i - 1].getRockPosition().y > 900)
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
				if (player.getGoldHalfHearts() > 0) {
					player.changeGoldHalfHearts(-1);

					cout << "You've been hit by a load of rocks! Your amount of gold half hearts is: " << player.getGoldHalfHearts() << endl;
				}
				else if (player.getHalfHearts() > 0) {
					player.changeHalfHearts(-1);

					cout << "You've been hit by a load of rocks! Your amount of half hearts is: " << player.getHalfHearts() << endl;
				}

				// erase the rock from the vector
				Rocks.erase(Rocks.begin() + (i - 1));
			}
		}
	}

}

void RockHandler::update(double deltaTime, Entity& player, const sf::Vector2f& target, int level[])
{
		handleRocks(deltaTime, player, target, fireRateTimer, maxFireRate, level, Walls);
		
}

void RockHandler::draw(sf::RenderWindow& window) {
	if (Health > 0)
	{
		window.draw(Sprite);
		window.draw(BoundingRectangle);

		for (size_t i = 0; i < Rocks.size(); i++)
			Rocks[i].drawRock(window);
	}
}









