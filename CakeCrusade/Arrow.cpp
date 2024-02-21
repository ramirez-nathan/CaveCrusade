#include "Arrow.hpp"
#include "Math.hpp"

Arrow::Arrow() 
    : m_speed(0.0f)
{
}

Arrow::~Arrow()
{
}

// initializes and loads the arrow texture
sf::Texture& Arrow::getArrowTexture()
{
    static sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("assets/player/textures/arrow.png")) {
        std::cerr << "Arrow texture failed to load!" << std::endl;
    }
    // returns arrow texture
    return arrowTexture;
}

// initializes an arrow sprite;
// - sets the texture, scale, position (@ player's position), and rotation (oriented towards the enemy)
sf::Sprite& Arrow::createArrowSprite(const sf::Texture& arrowTexture, const sf::Vector2f& position, const sf::Vector2f& direction)
{
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setScale(3.f, 3.f);
    arrowSprite.setPosition(position);
    // set origin at middle of sprite
    arrowSprite.setOrigin(arrowSprite.getLocalBounds().width / 2.f, arrowSprite.getLocalBounds().height / 2.f);
    // sets orientation to direction it was shot at
    arrowSprite.setRotation(atan2(direction.y, direction.x) * 180.0f / M_PI + 90.0f);
    // returns arrow sprite
    return arrowSprite;
}

// takes parameters: player position, mouseposition, arrow speed
void Arrow::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed) {
	m_speed = speed;
    // set arrow texture
    const sf::Texture& texture = getArrowTexture();
    // set arrow direction
    direction = Math::NormalizeVector(target - position);
    // set arrow sprite & its position
    arrowSprite = createArrowSprite(texture, position, direction);
	arrowSprite.setPosition(position);
}

void Arrow::Update(double deltaTime)
{
    arrowSprite.setPosition(arrowSprite.getPosition() + direction * m_speed * (float)deltaTime);
}
void Arrow::Draw(sf::RenderWindow& window)
{
	window.draw(arrowSprite);
}
