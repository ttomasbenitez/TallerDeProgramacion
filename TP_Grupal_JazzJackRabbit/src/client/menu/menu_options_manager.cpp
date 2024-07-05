#include "menu_options_manager.h"
#include "../backgrounds.h"
#include "colors.h"

#include "constants.h"

MenuOptionsManager::MenuOptionsManager(RendererManager *rendererManager, MusicManager *musicManager)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
}

void MenuOptionsManager::show(std::vector<std::string> options, std::vector<SDL_Color> mainColors)
{
    rendererManager->clear();
    buttons.clear();
    Texture *background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);

    int offset = 80;
    int i = 0;
    for (std::string option : options)
    {
        buttons.push_back(rendererManager->addText(option, FONTNAME, 40, VWIDTH + 4, VTHIRD + 4 + offset * i, COLOR_BLACK));
        rendererManager->addText(option, FONTNAME, 40, VWIDTH, VTHIRD + offset * i, mainColors.at(i));
        i++;
    }
    rendererManager->present();
}

void MenuOptionsManager::createMenu(std::vector<std::string> options, std::vector<SDL_Color> mainColors)
{
    show(options, mainColors);
}
