#include "Menu.hpp"
#include "Textbox.h"

Menu::Menu(sf::RenderWindow& window, bool isOver)
{
	sf::Sprite bg;
	sf::Texture bgtexture;

	if (!bgtexture.loadFromFile("assets/titlebackground.png"))
	{
		cout << "Failed to load Logo!" << endl;
	}

	bgtexture.setSmooth(false);
	bg.setTexture(bgtexture);
	bg.setPosition(sf::Vector2f(0.f, 0.f));

	drawMenu(window, bg);


	sf::Sprite logo;
	sf::Texture texture;

	if (!texture.loadFromFile("assets/Logo.png"))
	{
		cout << "Failed to load Logo!" << endl;
	}

	texture.setSmooth(false);
	logo.setTexture(texture);
	logo.setPosition(sf::Vector2f(415.f, 150.f));
	logo.scale(sf::Vector2f(7, 7));

	drawMenu(window, logo);

	sf::Sprite start;
	sf::Texture startTexture;

	if (!startTexture.loadFromFile("assets/pressEnter.png"))
	{
		cout << "Failed to load Logo!" << endl;
	}

	startTexture.setSmooth(false);
	start.setTexture(startTexture);
	start.setPosition(sf::Vector2f(640.f, 630.f));
	start.scale(sf::Vector2f(6, 6));

	if (!isOver) {
		drawMenu(window, start);
	}

	if (isOver) {
		MessageBox gameover;
		gameover.setText("GAME OVER", 510, 600, 70);
		gameover.drawMessageBox(window);
	}
}

Menu::~Menu()
{
}

void Menu::drawMenu(sf::RenderWindow& window, sf::Sprite s)
{
	window.draw(s);
}