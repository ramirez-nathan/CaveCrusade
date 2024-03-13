#pragma once
#ifndef ROCK_HPP
#define ROCk_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Rock
{
private:
	sf::Vector2f Direction;

	float RockSpeed;
public:
	sf::Sprite RockSprite;

public:
	Rock();
	~Rock();

	sf::Texture& getRockTexture();
	sf::Sprite& createRockSprite(const sf::Texture& rockTexture, const sf::Vector2f& position, const sf::Vector2f& direction);

	void initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed);
	bool didRockHitWall(double deltatime, const std::vector<int>& walls, const int level[]);
	void update(double deltaTime);
	void drawRock(sf::RenderWindow& window);

	inline const sf::FloatRect& getRockGlobalBounds() { return RockSprite.getGlobalBounds(); }
};

#endif