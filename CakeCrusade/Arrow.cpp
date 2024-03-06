#include "Arrow.hpp"
#include "Math.hpp"


Arrow::Arrow()
    : ArrowSpeed(0.0f)
{
}

Arrow::~Arrow()
{
}

// initializes and loads the arrow texture
sf::Texture& Arrow::getArrowTexture()
{
    static sf::Texture ArrowTexture;
    if (!ArrowTexture.loadFromFile("assets/player/textures/new_arrow.png")) {
        std::cerr << "Arrow texture failed to load!" << std::endl;
    }
    // returns arrow texture
    return ArrowTexture;
}

// initializes an arrow sprite;
// - sets the texture, scale, position (@ player's position), and rotation (oriented towards the enemy)
sf::Sprite& Arrow::createArrowSprite(const sf::Texture& arrowTexture, const sf::Vector2f& position, const sf::Vector2f& direction)
{
    ArrowSprite.setTexture(arrowTexture);
    ArrowSprite.setScale(3.f, 3.f);
    ArrowSprite.setPosition(position);
    // set origin at middle of sprite
    ArrowSprite.setOrigin(ArrowSprite.getLocalBounds().width / 2.f, ArrowSprite.getLocalBounds().height / 2.f);
    // sets orientation to direction it was shot at
    ArrowSprite.setRotation(atan2(direction.y, direction.x) * 180.0f / M_PI + 90.0f);
    // returns arrow sprite
    return ArrowSprite;
}

// takes parameters: player position, mouseposition, arrow speed
void Arrow::initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed) {
    ArrowSpeed = speed;
    // set arrow texture
    const sf::Texture& Texture = getArrowTexture();
    // set arrow direction
    Direction = Math::normalizeVector(target - position);
    // set arrow sprite & its position
    ArrowSprite = createArrowSprite(Texture, position, Direction);
    ArrowSprite.setPosition(position);
}

bool Arrow::didArrowHitWall(double deltaTime, const std::vector<int>& walls, const int level[])
{
    sf::Vector2f Position = ArrowSprite.getPosition();
    sf::Vector2f Movement = Direction * ArrowSpeed * (float)deltaTime;

    sf::Vector2f Future = Position + Movement;
    int futurePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if ((std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
        return true;
    }
    return false;
}
void Arrow::update(double deltaTime)
{
    ArrowSprite.setPosition(ArrowSprite.getPosition() + Direction * ArrowSpeed * (float)deltaTime);
}
void Arrow::drawArrow(sf::RenderWindow& window)
{
    window.draw(ArrowSprite);
}