#include "choose_scenery.h"
#include "../backgrounds.h"
#include "constants.h"

ChooseScenery::ChooseScenery(RendererManager *rendererManager, MusicManager *musicManager) : Choose(rendererManager, musicManager, {370, 0, 0}, std::vector<std::string>{"/scenery.png", backgrounds.at(Background::MAIN_SCREEN)})
{
}
void ChooseScenery::show()
{

    rendererManager->addBackground(sprites[1]);
    // Texture namePsych(*renderer, DATA_PATH + std::string("/names/psychedelia.png"));

    int vquarter = 480 / 4;       // Y coordinate of window center
    int hhalf = WINDOW_WIDTH / 2; // Y coordinate of window center

    int width = WINDOW_WIDTH * 0.4;
    int height = 480 * 0.4;

    // Muestra al escenario psicodelico

    rendererManager->copy(sprites[0], Rect(positions.at(0), 0, 370, 312), Rect(50, vquarter, width, height));
    // rendererManager->copy(namePsych, 0, 0, 420, 80, 50, vquarter + 200, width, height - 50);
    rendererManager->addText("Psychedelia", FONTNAME, 35, 60, 350, SDL_Color{255, 255, 255, 255});

    // Muestra al escenario2
    rendererManager->copy(sprites[0], Rect(positions.at(1), 312, 370, 312), Rect(hhalf, vquarter, width, height));
    rendererManager->addText("Beach world", FONTNAME, 35, 360, 350, SDL_Color{255, 255, 255, 255});

    // Show rendered frame
    rendererManager->present();
}

std::pair<int *, int *> ChooseScenery::obtainPosChanged(int actualChoosenObject)
{
    int *posSum;
    int *posSub;
    if (actualChoosenObject == 0)
    {
        posSum = &positions.at(1);
        posSub = &positions.at(0);
    }
    else if (actualChoosenObject == 1)
    {
        posSum = &positions.at(0);
        posSub = &positions.at(1);
    }

    return std::make_pair(posSum, posSub);
}

void ChooseScenery::animation(std::pair<int *, int *> &posChanged)
{

    updatePosition(posChanged, 370);
}

int ChooseScenery::chooseScenery()
{
    return choose(1);
}
