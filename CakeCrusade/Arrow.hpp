#ifndef ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
class Arrow
{
private:
	sf::Vector2f Direction;

	float ArrowSpeed;

public:
	sf::Sprite ArrowSprite;
public:
	Arrow();
	~Arrow();
	
	
	

	sf::Texture& getArrowTexture(const string& texturePath);
	sf::Sprite& createArrowSprite(const sf::Texture& arrowTexture, const sf::Vector2f& position, const sf::Vector2f& direction);

	void initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed, const string& texturePath);
	bool didArrowHitWall(double deltatime, const std::vector<int>& walls, const int level[]);
	void update(double deltaTime);
	void drawArrow(sf::RenderWindow& window);

	// need this helper function for grabbing global bounds at arrows[i]
	inline const sf::FloatRect& getArrowGlobalBounds() { return ArrowSprite.getGlobalBounds(); }
};

#endif 