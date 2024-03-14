#include "SoundFx.hpp"

SoundFx::SoundFx()
{
    sound.setPitch(1.0f);
    sound.setVolume(50.f);

    music.setLoop(true);
    music.setPitch(1.0f);
    music.setVolume(10.f);



}

bool SoundFx::loadMusic(string title)
{
    music.stop();

    if (!music.openFromFile(title))
        return false; // error

    else {
    music.play();
    }
}

bool SoundFx::loadSound(string title) {
    if (!Buffer.loadFromFile(title))
        return false; // error

    sound.setBuffer(Buffer);
    sound.play();
    return true;
}

