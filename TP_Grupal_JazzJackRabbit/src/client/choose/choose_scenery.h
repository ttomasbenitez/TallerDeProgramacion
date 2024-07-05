#ifndef __CHOOSE_SCENERY_H__
#define __CHOOSE_SCENERY_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include "choose.h"

class ChooseScenery : public Choose
{
private:
    void show();
    std::pair<int *, int *> obtainPosChanged(int actualChoosenObject);
    void animation(std::pair<int *, int *> &posChanged);

public:
    ChooseScenery(RendererManager *rendererManager, MusicManager *musicManager);
    int chooseScenery();
    ~ChooseScenery() {}
};

#endif