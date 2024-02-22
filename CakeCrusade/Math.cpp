#include "Math.hpp"
#include "Player.hpp"

// normalize vector function; divides x and y by the magnitude
sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
	float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	sf::Vector2f normalizedVector;

	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
}

//todo: tile collision

