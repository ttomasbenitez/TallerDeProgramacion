#ifndef __CHOOSE_CHARACTERS_H__
#define __CHOOSE_CHARACTERS_H__

#include "choose.h"

class ChooseCharacters : public Choose
{
protected:
    void show();
    std::pair<int *, int *> obtainPosChanged(int actualChoosenObject);
    void animation(std::pair<int *, int *> &posChanged);

public:
    ChooseCharacters(RendererManager *rendererManager, MusicManager *musicManager);
    int chooseCharacter();
    ~ChooseCharacters() {}
};

#endif