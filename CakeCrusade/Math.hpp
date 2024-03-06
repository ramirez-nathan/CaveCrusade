#pragma once
#include <SFML/Graphics.hpp>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Math
{
public:
	static sf::Vector2f normalizeVector(sf::Vector2f vector); // used for projectile direction vector
	static bool didRectCollide(sf::FloatRect rect1, sf::FloatRect rect2); // AABB Collision function

};