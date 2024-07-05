#include "choose.h"
#include "constant_rate.h"

Choose::Choose(RendererManager *rendererManager, MusicManager *musicManager, std::initializer_list<int> l, std::vector<std::string> spriteName) : positions{l}
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
    for (int i = 0; i < spriteName.size(); i++)
    {
        Texture* sprite = rendererManager->getTexture(spriteName[i]);
        sprites.push_back(std::move(sprite));
    }
}

void Choose::events(bool &hasChosen, bool &change, int &actual)
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                hasChosen = true;
                actual = -1;
                break;
            default:
                break;
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                change = true;
                musicManager->playMenuMove();
                break;
            case SDLK_SPACE:
                hasChosen = true;
                musicManager->playMenuSelect();
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                change = false;
                break;
            }
        }
    }
}

void Choose::updatePosition(std::pair<int *, int *> &posChanged, int offset)
{
    *(posChanged.first) += offset;
    *(posChanged.second) -= offset;
    show();
}

int Choose::choose(int maxOptions)
{
    rendererManager->clear();

    bool change = false;
    int actual = 0;

    show();

    ConstantRateLooper loop(30.0, [&](int _) {
        bool hasChosen = false;
        events(hasChosen, change, actual);

        if (change)
        {
            std::pair<int *, int *> posChanged = obtainPosChanged(actual);

            animation(posChanged);

            actual = (actual == maxOptions) ? 0 : actual + 1;
            change = false;
        }
        return !hasChosen;
    });
    loop.run();

    SDL_Delay(1);
    return actual;
}
