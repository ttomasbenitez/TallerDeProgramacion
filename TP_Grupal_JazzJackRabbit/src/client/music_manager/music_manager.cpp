#include "music_manager.h"

MusicManager::MusicManager(Mixer *mixer)
{
    this->mixer = mixer;
    menuMoveChunk = std::make_unique<Chunk>(DATA_PATH "/audio/move_menu.wav");
    menuSelectChunk = std::make_unique<Chunk>(DATA_PATH "/audio/select_menu.wav");
    background = std::make_unique<Music>(DATA_PATH "/audio/backgroundBeachLevel.wav");
    menuMusic = std::make_unique<Music>(DATA_PATH "/audio/menu.wav");
    sounds = initSoundMap();
}

bool MusicManager::playSound(AnimationState animationSound)
{
    auto it = sounds.find(animationSound);
    if (it != sounds.end())
    {
        mixer->PlayChannel(FIRST_FREE_CHANNEL, *(it->second), 0);
        return true;
    }
    return false;
}

void MusicManager::playLevelMusic()
{
    mixer->SetMusicVolume(MUSIC_VOLUME);
    mixer->PlayMusic(*background, -1);
}
void MusicManager::playMenuMusic()
{
    mixer->SetMusicVolume(MUSIC_VOLUME);
    mixer->PlayMusic(*menuMusic, -1);
}

void MusicManager::stopMusic()
{
    mixer->PauseMusic();
}

void MusicManager::playMenuMove()
{
    mixer->PlayChannel(FIRST_FREE_CHANNEL, *menuMoveChunk, 0);
}

void MusicManager::playMenuSelect()
{
    mixer->PlayChannel(FIRST_FREE_CHANNEL, *menuSelectChunk, 0);
}
