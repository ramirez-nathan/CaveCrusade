#include "Cutscene.hpp"

Cutscene::Cutscene(sf::RenderWindow& window)
{

	if (!bouldertexture.loadFromFile("assets/enemies/boulder/boulder.png", sf::IntRect(0, 0, 35, 38)))
	{
		cout << "Failed to load Boulder the Wizard!" << endl;
	}

	bouldertexture.setSmooth(false);
	boulder.setTexture(bouldertexture);
	boulder.setOrigin(boulder.getLocalBounds().width / 2.f, boulder.getLocalBounds().height / 2.f + 14);
	boulder.setPosition(sf::Vector2f(740.f, 390.f));
	boulder.setScale(3, 3);

	drawCutscene(window);

}

void Cutscene::drawCutscene(sf::RenderWindow& window)
{
	window.draw(boulder);
}
