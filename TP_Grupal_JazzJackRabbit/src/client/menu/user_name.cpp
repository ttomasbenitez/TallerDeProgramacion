#include "user_name.h"
#include "input_events_manager.h"
#include "cursor_manager.h"
#include "colors.h"

#include "../backgrounds.h"
#include "constants.h"
#include "constant_rate.h"

UserNameMenu::UserNameMenu(RendererManager *rendererManager, MusicManager *musicManager)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
    name = "";
    position = 0;
}

int UserNameMenu::events(bool &hasClosed)
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
                if (y >= 290 && y <= 340)
                {
                    if (x >= 240 && x <= 370)
                    {
                        if (name.size() <= 30)
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
                inputEventsManager.events(event, position, name);
            }
        }
    }
    return 0;
}

void UserNameMenu::showOptions(bool showCursor)
{
    rendererManager->clear();

    int posX = 205;
    int hwidth2 = 190;

    Texture *background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);
    std::string playerLabel = "Player name:";
    if (name.size() >= 30)
    {
        playerLabel += " exceeded 30 characters.";
    }
    if(name.size() == 0){
        name = " ";
    }
    Rect r = rendererManager->addText(playerLabel, FONTNAME, 20, posX, hwidth2, COLOR_WHITE);

    if (showCursor)
    {
        rendererManager->addTextBackground(name, FONTNAME, 40, posX + 2, hwidth2 + 2 + r.GetH(), COLOR_VIOLET, position, true);
    }
    else
    {
        rendererManager->addTextBackground(name, FONTNAME, 40, posX + 2, hwidth2 + 2 + r.GetH(), COLOR_VIOLET, position, false);
    }

    Texture *saveButton = rendererManager->getTexture("/continueFile.png");
    rendererManager->copy(saveButton, Rect(0, 0, 720, 360), Rect(240, 290, 130, 50));
    Texture *returnButton = rendererManager->getTexture("/returnFile.png");
    rendererManager->copy(returnButton, Rect(0, 0, 720, 360), Rect(380, 290, 125, 50));

    rendererManager->present();
}

std::pair<int, std::string> UserNameMenu::initUserNameMenu()
{
    int n = 0;
    bool hasClosed = false;
    bool showCursor = false;
    CursorManager cursorManager(BLINK_INTERVAL);

    showOptions(showCursor);

    ConstantRateLooper loop(30.0, [&] (int _){
        n = events(hasClosed);
        cursorManager.shouldBlink(showCursor);
        showOptions(showCursor);
        return !hasClosed;
    });
    loop.run();
    return std::make_pair(n, name);
}