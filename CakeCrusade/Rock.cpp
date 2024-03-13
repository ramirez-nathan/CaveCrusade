#include "Rock.hpp"
#include "Math.hpp"

Rock::Rock() 
{
}

Rock::~Rock() 
{
}

sf::Texture& Rock::getRockTexture() {
    static sf::Texture rockTexture;
    rockTexture.loadFromFile("assets/enemies/boss/Rocks.png");
    return rockTexture;
}

sf::Sprite& Rock::createRockSprite(const sf::Texture& rockTexture, const sf::Vector2f& position, const sf::Vector2f& direction) {
    RockSprite.setTexture(rockTexture);
    RockSprite.setScale(2.f, 2.f);
    RockSprite.setPosition(position);
    RockSprite.setOrigin(RockSprite.getLocalBounds().width / 2.f, RockSprite.getLocalBounds().height / 2.f);
    return RockSprite;
}

void Rock::initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed) {
    RockSpeed = speed;
    const sf::Texture& Texture = getRockTexture();
    sf::Vector2f rockDirection(0.0f, 100.0f);
    Direction = Math::normalizeVector(rockDirection);
    RockSprite = createRockSprite(Texture, position, Direction);
    RockSprite.setPosition(position);
}

bool Rock::didRockHitWall(double deltaTime, const std::vector<int>& walls, const int level[]) {
    sf::Vector2f Position = RockSprite.getPosition();
    sf::Vector2f Movement = Direction * RockSpeed * (float)deltaTime;

    sf::Vector2f Future = Position + Movement;
    int futurePos = floor(Future.y / 64) * 22 + floor(Future.x / 64);
    if ((std::find(walls.begin(), walls.end(), level[futurePos]) != walls.end())) {
        return true;
    }
    return false;
}

void Rock::update(double deltaTime) {
   RockSprite.setPosition(RockSprite.getPosition() + Direction * RockSpeed * (float)deltaTime);
}

void Rock::drawRock(sf::RenderWindow& window) {
    window.draw(RockSprite);
}
