#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <iostream>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>
#include <memory>
#include "sounds_map.h"
#include "../../common/gamestate.h"

#define FIRST_FREE_CHANNEL (-1)
#define MUSIC_VOLUME 40

class MusicManager
{
private:
    Mixer *mixer;
    std::unique_ptr<Chunk> menuMoveChunk;
    std::unique_ptr<Chunk> menuSelectChunk;
    std::unique_ptr<Music> background;
    std::unique_ptr<Music> menuMusic;
    std::unordered_map<AnimationState, std::unique_ptr<Chunk>> sounds;

public:
    MusicManager(Mixer *mixer);
    void playMenuMusic();
    void playMenuMove();
    void playMenuSelect();
    bool playSound(AnimationState animationSound);
    void playLevelMusic();
    void stopMusic();
    ~MusicManager() = default;
};

#endif // MUSIC_MANAGER_H
