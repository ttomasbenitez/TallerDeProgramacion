#include "choose_characters.h"
#include "../backgrounds.h"
#include "constants.h"

ChooseCharacters::ChooseCharacters(RendererManager *rendererManager, MusicManager *musicManager) : Choose(rendererManager, musicManager, {1125, 0, 0}, std::vector<std::string>{"/characters.png", "/names/Jazz_name.png", "/names/Spaz_name.png", "/names/Lori_name.png", backgrounds.at(Background::MAIN_SCREEN)})
{
}
void ChooseCharacters::show()
{

    rendererManager->addBackground(sprites[4]);

    // int posName =  positions.at(0) - 1125;
    int vthird = WINDOW_HEIGHT / 2; // Y coordinate of window center
    int vhalf = WINDOW_HEIGHT / 2;  // Y coordinate of window center

    // Muestra al personaje Jazz 125
    rendererManager->copy(sprites[1], Rect(positions.at(0) - 1125, 0, 130, 110), Rect(14 + 35, vthird - 125, 215 - 50, 215 - 50));
    rendererManager->copy(sprites[0], Rect(positions.at(0), 0, 125, 180), Rect(14, vthird, 215, 215));

    // Muestra al personaje a spaz
    rendererManager->copy(sprites[2], Rect(positions.at(1) - 1125, 0, 130, 74), Rect(233 + 35, vthird - 125, 215 - 50, 215 - 50));
    rendererManager->copy(sprites[0], Rect(positions.at(1), 185, 105, 200), Rect(233, vthird, 215, 215));

    // Muestra al personaje a lori
    rendererManager->copy(sprites[3], Rect(positions.at(2) - 1125, 0, 127, 109), Rect(466 + 35, vthird - 125, 215 - 50, 215 - 50));
    rendererManager->copy(sprites[0], Rect(positions.at(2), 408, 115, 185), Rect(466, vthird, 215, 215));

    // Show rendered frame
    rendererManager->present();
}

std::pair<int *, int *> ChooseCharacters::obtainPosChanged(int actualChoosenObject)
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
        posSum = &positions.at(2);
        posSub = &positions.at(1);
    }
    else if (actualChoosenObject == 2)
    {
        posSum = &positions.at(0);
        posSub = &positions.at(2);
    }
    return std::make_pair(posSum, posSub);
}

void ChooseCharacters::animation(std::pair<int *, int *> &posChanged)
{
    for (int i = 0; i < 9; i++)
    {
        updatePosition(posChanged, 125);
        SDL_Delay(50);
    }
}

int ChooseCharacters::chooseCharacter()
{
    return choose(2);
}
