#ifndef ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Arrow
{
private:
	sf::Vector2f direction;

	float m_speed;

public: 
	sf::Sprite arrowSprite;
public:
	Arrow();
	~Arrow();

	sf::Texture& getArrowTexture();
	sf::Sprite& createArrowSprite(const sf::Texture& arrowTexture, const sf::Vector2f& position, const sf::Vector2f& direction);

	void Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed);
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

	// need this helper function for grabbing global bounds at arrows[i]
	inline const sf::FloatRect& GetGlobalBounds() { return arrowSprite.getGlobalBounds(); }  
};

#endif 