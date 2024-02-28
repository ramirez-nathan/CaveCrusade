#include "Math.hpp"
#include "Player.hpp"

// normalize vector function; divides x and y by the magnitude
sf::Vector2f Math::normalizeVector(sf::Vector2f vector)
{
	float Magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	sf::Vector2f NormalizedVector;

	NormalizedVector.x = vector.x / Magnitude;
	NormalizedVector.y = vector.y / Magnitude;

	return NormalizedVector;
}

// AABB Collision function
bool Math::didRectCollide(sf::FloatRect rect1, sf::FloatRect rect2)
{
	if (rect1.left + rect1.width > rect2.left &&
		rect2.left + rect1.width > rect1.left &&
		rect2.top + rect2.height > rect1.top &&
		rect1.top + rect1.height > rect2.top)
		return true;

	return false;
}


