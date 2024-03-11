#include "SoundFx.hpp"

SoundFx::SoundFx()
{
    loadMusicTitle = "sound/music/andthejourneybegins.wav";

    if (!music.openFromFile(loadMusicTitle))
        cout << "Music failed!"; // error

    music.setLoop(true);
    music.setPitch(1.f);
    music.setVolume(20.f);
    music.play();
}

bool SoundFx::loadMusic(string title)
{
    music.stop();

    if (!music.openFromFile(title))
        return false; // error
    music.play();
}


