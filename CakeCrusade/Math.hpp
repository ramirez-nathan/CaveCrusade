#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "math.h"
#include "vector"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;
class Math 
{
public:
	static sf::Vector2f NormalizeVector(sf::Vector2f vector); // used for projectile direction vector
	static bool DidRectCollide(sf::FloatRect rect1, sf::FloatRect rect2); // AABB Collision function
	static void CorrectRectCollision(sf::FloatRect& rect1, sf::FloatRect& rect2);
	static void Collider(Entity& player, Entity& enemy, int level[]);
};