
#include "menu_level_editor.h"
#include "../level_editor/model/palette/element_reader.h"
#include "../level_editor/controller/create_level.h"
#include "../level_editor/controller/level_edit.h"
#include "../backgrounds.h"
#include "maps_menu.h"
#include "create_file_menu.h"
#include "constants.h"

#include "colors.h"

#include "../choose/choose_scenery.h"
#include "constant_rate.h"

MenuLevelEditor::MenuLevelEditor(RendererManager *rendererManager, MusicManager *musicManager) : MenuOptionsManager(rendererManager, musicManager)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
}

int MenuLevelEditor::initMenu(Window *window)
{
    bool hasClosed = false;
    this->window = window;
    int n = -1;
    createMenu({"Create level", "Edit level", "Return"}, {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE});
    ConstantRateLooper loop(30.0, [&](int _)
                            {
        n = events(hasClosed);
        return !hasClosed; });
    loop.run();
    return n;
}

void MenuLevelEditor::returnToMenu()
{
    SDL_SetWindowSize(window->Get(), WINDOW_WIDTH, WINDOW_HEIGHT);
    createMenu({"Create level", "Edit level", "Return"}, {COLOR_WHITE, COLOR_WHITE, COLOR_WHITE});
}

void MenuLevelEditor::checkHasClosed(int n, bool &hasClosed)
{
    if (n != -1)
    {
        returnToMenu();
    }
    else
    {
        hasClosed = true;
    }
}

void MenuLevelEditor::editLevels(bool &hasClosed)
{
    std::string filename;
    MapsMenu mapsMenu(rendererManager, musicManager);
    filename = mapsMenu.initMenu();
    if (filename == "")
    {
        hasClosed = true;
    }
    else
    {
        LevelParser levelParser(filename.c_str());
        SDL_SetWindowSize(window->Get(), 1000, WINDOW_HEIGHT);
        LevelEdit levelEdit(rendererManager, &levelParser, filename);
        checkHasClosed(levelEdit.run(), hasClosed);
    }
}

void MenuLevelEditor::createLevels(bool &hasClosed)
{
    ChooseScenery scenery(rendererManager, musicManager);
    int numbOfScenery = scenery.chooseScenery();
    if (numbOfScenery == -1)
    {
        hasClosed = true;
    }
    else
    {
        CreateFileMenu createFileMenu(rendererManager, musicManager);
        std::pair<int, std::pair<std::string, std::string>> fileData = createFileMenu.initMenu();
        if (fileData.first == -1)
        {
            hasClosed = true;
        }
        else if (fileData.first == 0)
        {
            SDL_SetWindowSize(window->Get(), 1000, WINDOW_HEIGHT);
            CreateLevel createLevel(rendererManager, numbOfScenery, fileData.second.first, fileData.second.second);
            checkHasClosed(createLevel.run(), hasClosed);
        }
        else
        {
            returnToMenu();
        }
    }
}

int MenuLevelEditor::events(bool &hasClosed)
{

    SDL_Event event;
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
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            Rect mouse = {event.motion.x, event.motion.y, 10, 10};

            if (mouse.Intersects(buttons[0]))
            {
                musicManager->playMenuSelect();

                createLevels(hasClosed);
            }
            else if (mouse.Intersects(buttons[1]))
            {
                musicManager->playMenuSelect();

                editLevels(hasClosed);
            }
            else if (mouse.Intersects(buttons[2]))
            {
                musicManager->playMenuSelect();

                hasClosed = true;
                return 0;
            }
        }
        else
        {
        }
    }
    return -1;
}