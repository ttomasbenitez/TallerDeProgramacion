
#include "menu.h"
#include <cstdio>
#include "../choose/choose_characters.h"
#include "../choose/choose_scenery.h"
#include "../backgrounds.h"
#include "join_menu.h"
#include "menu_level_editor.h"
#include "maps_menu.h"
#include "user_name.h"

#include "colors.h"
#include "constant_rate.h"

Menu::Menu(RendererManager *rendererManager, MusicManager *musicManager, Queue<ClientAction> &actionQueue, Queue<GameState> &responseQueue) : MenuOptionsManager(rendererManager, musicManager), actionQueue(actionQueue), responseQueue(responseQueue)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
    this->isEditing = false;
}

void Menu::initMenu(gameInformation &game, Window *window)
{
    createMenu({
                   "Play",
                   "Edit levels",
               },
               {COLOR_WHITE, COLOR_WHITE});
    ConstantRateLooper loop(30.0, [&](int _)
                            {
        bool hasClosed = false;
        this->events(hasClosed, game, window);
        return !hasClosed; });
    try
    {
        loop.run();
    }
    catch (const ClosedQueue &e)
    {
        this->show({"No connection", "Shuting down"}, {COLOR_WHITE, COLOR_WHITE});
        SDL_Delay(1000);
    }
}

bool Menu::joinCreateMenu(gameInformation &game, Window *window, bool &hasClosed)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                hasClosed = true;
                return false;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            Rect mouse = {event.motion.x, event.motion.y, 10, 10};
            if (mouse.Intersects(buttons[0]))
            {

                game.hasCreatedGame = false;
                game.gameId = 0;
                return true;
            }
            else if (mouse.Intersects(buttons[1]))
            {
                game.hasCreatedGame = true;
                return true;
            }
            else if (mouse.Intersects(buttons[2]))
            {
                game.hasCreatedGame = false;
                game.gameId = -1;
                return true;
            }
        }
    }
    return false;
}

int Menu::chooseCharacter()
{
    ChooseCharacters character(rendererManager, musicManager);
    return character.chooseCharacter();
}

int Menu::editLevels(Window *window)
{
    MenuLevelEditor menuLevelEditor(rendererManager, musicManager);
    return menuLevelEditor.initMenu(window);
}

void Menu::events(bool &hasClosed, gameInformation &game, Window *window)
{
    std::vector<SDL_Color> mainMenuColors = {COLOR_WHITE, COLOR_WHITE};
    std::vector<SDL_Color> gameMenumainColors = {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE};
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_WINDOWEVENT)
        {

            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                hasClosed = true;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !isEditing)
        {
            Rect mouse = {event.motion.x, event.motion.y, 10, 10};
            int x = event.motion.x;
            int y = event.motion.y;

            if (mouse.Intersects(buttons[0]))
            {
                musicManager->playMenuSelect();
                UserNameMenu userNameMenu(rendererManager, musicManager);
                std::pair<int, std::string> dataName = userNameMenu.initUserNameMenu();
                if (dataName.first == -1)
                {
                    hasClosed = true;
                    return;
                }
                else if (dataName.first == 1)
                {
                    createMenu({"Play", "Edit levels"}, {COLOR_WHITE, COLOR_WHITE});
                    return;
                }
                game.name = dataName.second;

                createMenu({"Join Game", "Create Game", "Return"}, {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE});
                ConstantRateLooper joinloop(30.0, [&](int _)
                                            { return !joinCreateMenu(game, window, hasClosed) && !hasClosed; });
                joinloop.run();
                if (game.hasCreatedGame)
                {
                    std::string filename;
                    MapsMenu mapsMenu(rendererManager, musicManager);
                    filename = mapsMenu.initMenu();
                    if (filename == "")
                    {
                        hasClosed = true;
                        return;
                    }
                    game.mapPath = filename;
                    int numbOfCharacter = chooseCharacter();
                    game.characterId = numbOfCharacter;
                    hasClosed = true;
                    return;
                }

                else if (game.hasCreatedGame == false && game.gameId == 0 && !hasClosed)
                {
                    JoinMenu joinMenu(rendererManager, actionQueue, responseQueue);
                    game.gameId = joinMenu.join();
                    if (game.gameId != -1)
                    {
                        int numbOfCharacter = chooseCharacter();
                        game.characterId = numbOfCharacter;
                        hasClosed = true;
                        return;
                    }
                }
                if (hasClosed == false && (game.hasCreatedGame == false && game.gameId == -1))
                {
                    createMenu({"Play", "Edit levels"}, {COLOR_WHITE, COLOR_WHITE});

                    continue;
                }
            }
            else if (mouse.Intersects(buttons[1]))
            {
                musicManager->playMenuSelect();
                isEditing = true;

                int n = editLevels(window);
                if (n == -1)
                {
                    hasClosed = true;
                }
                else
                {
                    createMenu({"Play", "Edit levels"}, {COLOR_WHITE, COLOR_WHITE});
                    isEditing = false;
                }
            }
            else
            {
            }
        }
    }
}