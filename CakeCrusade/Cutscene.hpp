#pragma once
#pragma once

#include <SFML/Audio.hpp>
#include <string> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Textbox.h"

using namespace std;

class Cutscene {
public:

	Cutscene(sf::RenderWindow& window);
	~Cutscene();
	sf::Sprite boulder;
	sf::Texture bouldertexture;
	MessageBox messageBox;


	void drawCutscene(sf::RenderWindow& window);

};