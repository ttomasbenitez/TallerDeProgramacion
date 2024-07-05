#include "create_file_menu.h"

#include "../backgrounds.h"
#include "input_events_manager.h"
#include "cursor_manager.h"
#include "constants.h"
#include "colors.h"
#include "constant_rate.h"

CreateFileMenu::CreateFileMenu(RendererManager *rendererManager, MusicManager *musicManager)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
    Input inputFilename = {"", true, 0};
    Input inputMapName = {"", false, 0};
    inputs.push_back(inputFilename);
    inputs.push_back(inputMapName);
    selected = 0;
}

int CreateFileMenu::events(bool &hasClosed)
{
    SDL_Event event;
    InputEventsManager inputEventsManager;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                hasClosed = true;
                return -1;
            }
        }
        else
        {
            int x = event.motion.x;
            int y = event.motion.y;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                if (x >= 205 && x <= 555)
                {
                    if (y <= 151 + 48 && y >= 151)
                    {
                        selected = 0;
                        inputs.at(0).isSelected = true;
                        inputs.at(1).isSelected = false;
                    }
                    else if (y <= 266 + 48 && y >= 266)
                    {
                        selected = 1;
                        inputs.at(1).isSelected = true;
                        inputs.at(0).isSelected = false;
                    }
                }
                if (y >= 350 && y <= 400)
                {
                    if (x >= 240 && x <= 370)
                    {
                        if (inputs.at(0).name.size() > 0)
                        {
                            musicManager->playMenuSelect();
                            hasClosed = true;
                            return 0;
                        }
                    }
                    else if (x >= 380 && x <= 505)
                    {
                        musicManager->playMenuSelect();
                        hasClosed = true;
                        return 1;
                    }
                }
            }
            else
            {
                inputEventsManager.events(event, inputs.at(selected).position, inputs.at(selected).name);
            }
        }
    }
    return 0;
}

std::pair<int, std::pair<std::string, std::string>> CreateFileMenu::initMenu()
{
    int n = 0;
    bool hasClosed = false;
    bool showCursor = false;
    CursorManager cursorManager(BLINK_INTERVAL);

    showOptions(showCursor);
    ConstantRateLooper loop(30.0, [&](int _)
                            {
        n = events(hasClosed);
        cursorManager.shouldBlink(showCursor);
        showOptions(showCursor);
        return !hasClosed; });
    loop.run();
    return std::make_pair(n, std::make_pair(inputs.at(0).name, "/" + inputs.at(1).name));
}

void CreateFileMenu::showOptions(bool showCursor)
{
    rendererManager->clear();

    int posX = 205;

    Texture *background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);

    std::string mapNameLabel = "Map name:";
    if (inputs.at(0).name.size() == 0)
    {
        mapNameLabel += " at least 1 character.";
    }
    Rect r = rendererManager->addText(mapNameLabel, FONTNAME, 20, posX, 125, COLOR_WHITE);

    Rect filenameLabel = rendererManager->addText("Map filename: (add .yaml)", FONTNAME, 20, posX, VWIDTH, COLOR_WHITE);

    if (showCursor)
    {
        rendererManager->addTextBackground(inputs.at(0).name, FONTNAME, 40, posX + 2, 125 + 2 + r.GetH(), COLOR_VIOLET, inputs.at(0).position, inputs.at(0).isSelected);
        rendererManager->addTextBackground(inputs.at(1).name, FONTNAME, 40, posX + 2, VWIDTH + 2 + filenameLabel.GetH(), COLOR_VIOLET, inputs.at(1).position, inputs.at(1).isSelected);
    }
    else
    {
        rendererManager->addTextBackground(inputs.at(0).name, FONTNAME, 40, posX + 2, 125 + 2 + r.GetH(), COLOR_VIOLET, inputs.at(0).position, false);
        rendererManager->addTextBackground(inputs.at(1).name, FONTNAME, 40, posX + 2, VWIDTH + 2 + filenameLabel.GetH(), COLOR_VIOLET, inputs.at(1).position, false);
    }

    Texture *saveButton = rendererManager->getTexture("/continueFile.png");
    rendererManager->copy(saveButton, Rect(0, 0, 720, 360), Rect(240, 350, 130, 50));
    Texture *returnButton = rendererManager->getTexture("/returnFile.png");
    rendererManager->copy(returnButton, Rect(0, 0, 720, 360), Rect(380, 350, 125, 50));

    rendererManager->present();
}