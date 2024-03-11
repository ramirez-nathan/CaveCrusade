#include "SoundFx.hpp"

SoundFx::SoundFx()
{
    loadMusicTitle = "sound/music/andthejourneybegins.wav";

    if (!music.openFromFile(loadMusicTitle))
        cout << "Music failed!"; // error

    music.setLoop(true);
    music.setPitch(1.0f);
    music.setVolume(10.f);
    music.play();
}

bool SoundFx::loadMusic(string title)
{
    music.stop();

    if (!music.openFromFile(title))
        return false; // error
    music.play();
}


