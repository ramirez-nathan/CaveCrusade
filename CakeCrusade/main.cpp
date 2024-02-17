#include <SFML/Graphics.hpp>
#include <iostream>

// SFML Experimenting --- Shapes ---
int main()
{
	//-------------------------------- INITIALIZE --------------------------------

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cake Crusade", sf::Style::Default, settings);

	//-------------------------------- INITIALIZE --------------------------------

	// ------------------------------- LOAD ----------------------------------
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	int playerXIndex = 0;
	int playerYIndex = 0;
	int width = 32;
	int height = 32;
	if (playerTexture.loadFromFile("assets/player/textures/player_idle.png"))
	{
		std::cout << "Player image loaded successfully!" << std::endl;
		playerSprite.setTexture(playerTexture);

		// INT RECT
		// X, Y, Width, Height
		playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
		playerSprite.scale(sf::Vector2f(3, 3));
	}
	else
	{
		std::cout << "Player image failed to load!" << std::endl;
	}

	// ------------------------------- LOAD ----------------------------------


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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerXIndex = 0;
			playerYIndex = 1;
			playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
			sf::Vector2f position = playerSprite.getPosition();
			playerSprite.setPosition(position + sf::Vector2f(0, -1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerXIndex = 0;
			playerYIndex = 2;
			playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
			sf::Vector2f position = playerSprite.getPosition();
			playerSprite.setPosition(position + sf::Vector2f(-1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerXIndex = 0;
			playerYIndex = 0;
			playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
			sf::Vector2f position = playerSprite.getPosition();
			playerSprite.setPosition(position + sf::Vector2f(0, 1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
			playerXIndex = 0;
			playerYIndex = 3;
			playerSprite.setTextureRect(sf::IntRect(playerXIndex * 32, playerYIndex * 32, width, height));
			sf::Vector2f position = playerSprite.getPosition();
			playerSprite.setPosition(position + sf::Vector2f(1, 0));
		}

		//-------------------------------- UPDATE --------------------------------

		//-------------------------------- DRAW --------------------------------
		window.clear(sf::Color::Black);
		window.draw(playerSprite);
		window.display();
		//-------------------------------- DRAW --------------------------------
	}

	return 0;
}