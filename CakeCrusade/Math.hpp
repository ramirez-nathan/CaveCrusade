#pragma once
#include <SFML/Graphics.hpp>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Math 
{
public:
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
};