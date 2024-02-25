#include "Player.hpp"
#include "Math.hpp"

Player::Player(float h, float dmg, float def) 
   : Entity(h, def, dmg), playerSpeed(0.5f), maxFireRate(150), fireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    size = sf::Vector2i(32, 32);
}

void Player::Load() 
{
    // check if texture loaded correctly
    if (!texture.loadFromFile("assets/player/textures/player_idle.png"))
    {
        std::cerr << "Player texture failed to load!" << std::endl;
    }
    // set texture
    playerSprite.setTexture(texture);
    // grab the idle texture image from spritesheet
    playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
    // set spawn position
    playerSprite.setPosition(sf::Vector2f(600, 300));
    // set origin at middle of sprite
    playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2.f, playerSprite.getLocalBounds().height / 2.f);
    // change sprite scale
    playerSprite.scale(sf::Vector2f(3, 3));
}

// takes parameters - deltatime, any specified entity (by upcasting), and mouseposition
void Player::Update(double deltaTime, Entity& enemy, sf::Vector2f& mousePosition)
{
    
    // WASD MOVEMENT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        XIndex = 0;
        YIndex = 1;
        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sf::Vector2f position = playerSprite.getPosition();
        playerSprite.setPosition(position + sf::Vector2f(0, -1) * playerSpeed * (float)deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        XIndex = 0;
        YIndex = 0;
        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sf::Vector2f position = playerSprite.getPosition();
        playerSprite.setPosition(position + sf::Vector2f(0, 1) * playerSpeed * (float)deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        XIndex = 0;
        YIndex = 2;
        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sf::Vector2f position = playerSprite.getPosition();
        playerSprite.setPosition(position + sf::Vector2f(-1, 0) * playerSpeed * (float)deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        XIndex = 0;
        YIndex = 3;
        playerSprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sf::Vector2f position = playerSprite.getPosition();
        playerSprite.setPosition(position + sf::Vector2f(1, 0) * playerSpeed * (float)deltaTime);
    }
    //---------------------------------------------- ARROWS -------------------------------------------------
    fireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate)
    {
        arrows.push_back(Arrow());
        int i = arrows.size() - 1;
        arrows[i].Initialize(playerSprite.getPosition(), mousePosition, 0.5f);
        fireRateTimer = 0;
    }

    for (size_t i = 0; i < arrows.size(); i++)
    {
        arrows[i].Update(deltaTime);

        /*if (enemy.health > 0)
        {
            // implement this when collision is finished 
            if (Math::DidRectCollide(arrows[i].GetGlobalBounds(), enemy.sprite.getGlobalBounds()))
            {
                soldier.ChangeHealth(-10);
                arrows.erase(arrows.begin() + i);
            }
        }*/
    }

    //---------------------------------------------- ARROWS -------------------------------------------------


}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(playerSprite);

    // draw each arrow sprite in vector
    for (size_t i = 0; i < arrows.size(); i++)
        arrows[i].Draw(window);
}

void Player::attackMove() {
    // Implement how the enemy attacks
}