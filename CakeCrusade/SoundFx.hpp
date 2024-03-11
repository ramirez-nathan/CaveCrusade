#pragma once

#include <SFML/Audio.hpp>
#include <string> 
#include <iostream> 

using namespace std; 

class SoundFx {
public:
	
	SoundFx();
	sf::SoundBuffer Buffer;
	sf::Music music;

	string loadMusicTitle; 

	bool loadMusic(string title);
	

};
