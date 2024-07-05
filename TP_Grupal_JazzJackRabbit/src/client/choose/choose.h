#ifndef __CHOOSE_H__
#define __CHOOSE_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "../renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"
class Choose
{
protected:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    std::vector<int> positions;
    std::vector<Texture*> sprites;

    virtual void show() = 0;
    virtual std::pair<int *, int *> obtainPosChanged(int actualChoosenObject) = 0;
    virtual void animation(std::pair<int *, int *> &posChanged) = 0;

    int choose(int maxOptions);
    void updatePosition(std::pair<int *, int *> &posChanged, int offset);
    // modularizar
    void events(bool &hasChosenCharacter, bool &changeCharacters, int &actualCharacter);

public:
    Choose(RendererManager *rendererManager, MusicManager *musicManager, std::initializer_list<int> l, std::vector<std::string> spriteName);
};

#endif