#pragma once

#include <SFML/Audio.hpp>
#include <string> 
#include <iostream> 

using namespace std; 

class SoundFx {
public:
	
	SoundFx();
	sf::SoundBuffer Buffer;
	sf::Sound sound;

	sf::Music music;

	string loadMusicTitle; 

	bool loadMusic(string title);
	bool loadSound(string title);
	

};
