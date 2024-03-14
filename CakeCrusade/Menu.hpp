#pragma once

#include <SFML/Audio.hpp>
#include <string> 
#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace std;

class Menu {
public:

	Menu(sf::RenderWindow& window);

	void drawMenu(sf::RenderWindow& window, sf::Sprite s);

};