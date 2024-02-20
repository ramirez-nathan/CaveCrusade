#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "TileMap.cpp"
#include "Player.cpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std; 

sf::Vector2f NormalizeVector(sf::Vector2f vector) 
{
    float m = sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;

    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;

    return normalizedVector;
}

// --------------------- ARROW SPRITE FUNCTIONS -------------------------
sf::Texture& getArrowTexture() {
    static sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("assets/player/textures/arrow.png")) {
        std::cerr << "Arrow texture failed to load!" << std::endl;
    }
    return arrowTexture;
}

sf::Sprite& createArrowSprite(const sf::Texture& arrowTexture, const sf::Vector2f& position, const sf::Vector2f& direction) {
    static sf::Sprite arrowSprite;
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setScale(3.f, 3.f);
    arrowSprite.setPosition(position);
    arrowSprite.setOrigin(arrowSprite.getLocalBounds().width / 2.f, arrowSprite.getLocalBounds().height / 2.f);
    arrowSprite.setRotation(atan2(direction.y, direction.x) * 180.0f / M_PI + 90.0f);
    return arrowSprite;
}
// --------------------- ARROW SPRITE FUNCTIONS -------------------------

 
// SFML Experimenting --- Shapes ---
int main()
{
    //-------------------------------- INITIALIZE --------------------------------

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1408, 704), "Cake Crusade", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    //-------------------------------- INITIALIZE --------------------------------
    
    
    // ------------------------------------------ LOAD ---------------------------------

    // ------------------------------- TILEMAP ----------------------------------
    // define the level with an array of tile indices
    const int level[] =
    {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 4, 5, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    };
    TileMap map;
    if (!map.load("assets/tilemap/tileset.png", sf::Vector2u(16, 16), level, 22, 11)) 
        return -1;
    // ------------------------------- TILEMAP ----------------------------------

    
    // ------------------------------- SOLDIER ----------------------------------
    sf::Texture soldierTexture;
    sf::Sprite soldierSprite;
    int soldierXIndex = 0;
    int soldierYIndex = 0;
    int soldierWidth = 32;
    int soldierHeight = 32;
    if (soldierTexture.loadFromFile("assets/enemies/evil_soldier/textures/evil_soldier_idle.png"))
    {
        std::cout << "Enemy texture lodaded successfully!" << std::endl;
        soldierSprite.setTexture(soldierTexture);

        // INT RECT
        // X, Y, Width, Height
        soldierSprite.setTextureRect(sf::IntRect(soldierXIndex * 32, soldierYIndex * 32, soldierWidth, soldierHeight));
        soldierSprite.setPosition(sf::Vector2f(400, 100));
        soldierSprite.scale(sf::Vector2f(3, 3));
        soldierSprite.setOrigin(soldierSprite.getLocalBounds().width / 2.f, soldierSprite.getLocalBounds().height / 2.f);
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
    // ------------------------------- SOLDIER ----------------------------------
  
    // ------------------------------- PLAYER ----------------------------------
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int playerXIndex = 0;
    int playerYIndex = 0;
    int width = 32;
    int height = 32;
    if (playerTexture.loadFromFile("assets/player/textures/player_idle.png"))
    {
        std::cout << "Player texture loaded successfully!" << std::endl;
        playerSprite.setTexture(playerTexture);

        // INT RECT
        // X, Y, Width, Height
        playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
        playerSprite.setPosition(sf::Vector2f(500,200));
        playerSprite.scale(sf::Vector2f(3, 3));
        playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2.f, playerSprite.getLocalBounds().height / 2.f);
    }
    else
    {
        std::cout << "Player texture failed to load!" << std::endl;
    }

    // ------------------------------- PLAYER ----------------------------------
    
    // ----------------------------- ARROW --------------------------
    vector<sf::Sprite> arrowSprites;
    float arrowSpeed = 3.5f;
    // ----------------------------- ARROW --------------------------

    // ------------------------------------------ LOAD ---------------------------------


    //main game loop
    while (window.isOpen())
    {
        //-------------------------------- UPDATE --------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // WASD MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            playerXIndex = 0;
            playerYIndex = 1;
            playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            playerXIndex = 0;
            playerYIndex = 0;
            playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, 1));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            playerXIndex = 0;
            playerYIndex = 2;
            playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            playerXIndex = 0;
            playerYIndex = 3;
            playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(1, 0));
        }
        // SHOOT ARROW
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            // set arrow texture
            const sf::Texture& arrowTexture = getArrowTexture();
            // set arrow direction
            sf::Vector2f arrowDirection = soldierSprite.getPosition() - playerSprite.getPosition();
            arrowDirection = NormalizeVector(arrowDirection);
            // set arrow sprite
            sf::Sprite& arrowSprite = createArrowSprite(arrowTexture, playerSprite.getPosition(), arrowDirection);
            arrowSprites.push_back(arrowSprite);
        }

        // LOOPS THROUGH VECTOR, UPDATES DIRECTION AND POSITION FOR EACH ARROW SPRITE
        for (size_t i = 0; i < arrowSprites.size(); i++)
        {
            sf::Vector2f arrowDirection = soldierSprite.getPosition() - arrowSprites[i].getPosition();
            arrowDirection = NormalizeVector(arrowDirection);
            arrowSprites[i].setPosition(arrowSprites[i].getPosition() + arrowDirection * arrowSpeed);
        }
        //-------------------------------- UPDATE --------------------------------

        //-------------------------------- DRAW --------------------------------
        window.clear();
        window.draw(map);
        window.draw(soldierSprite);
        window.draw(playerSprite);
        // draw each arrow sprite in vector
        for (size_t i = 0; i < arrowSprites.size(); i++)
        {
            window.draw(arrowSprites[i]);
        }
        window.display();
        //-------------------------------- DRAW --------------------------------
    }
    
    return 0;
}