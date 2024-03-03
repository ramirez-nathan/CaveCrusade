#include "Math.hpp"
#include "Player.hpp"

// normalize vector function; divides x and y by the magnitude

//todo: tile collision


sf::Vector2f Math::NormalizeVector(sf::Vector2f vector)
{
    float Magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    // Avoid division by zero
    if (Magnitude != 0.0f)
    {
        sf::Vector2f NormalizedVector;
        NormalizedVector.x = vector.x / Magnitude;
        NormalizedVector.y = vector.y / Magnitude;
        return NormalizedVector;
    }
    else
    {
        // Handle the case when the magnitude is zero (e.g., return a default vector)
        return sf::Vector2f(0.0f, 0.0f);
    }
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