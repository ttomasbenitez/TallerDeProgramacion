#include "../model/palette/element_reader.h"
#include "common_editor.h"
#include "../model/events_manager.h"
#include "create_level.h"
#include "../model/colission_checker.h"
#include "../view/graphics_level_editor.h"
#include "../../backgrounds.h"
#include "../model/events_manager.h"

#define WAIT_TIMEOUT 7

CommonEditor::CommonEditor(RendererManager *rendererManager, int scenery, std::string filename) : palette(rendererManager, scenery), camera()
{
    this->rendererManager = rendererManager;
    this->filename = filename;
}

void CommonEditor::initCommonEditor()
{
    run();
}

int CommonEditor::selectEntityToEdit()
{

    bool quit = false;
    SDL_Event event;
    bool scroll = false;
    int selectedEntityID = -1, scrollSpeed = -1, n = -1;
    int opacity = 0;
    int x = 0;
    int y = 0;
    std::string buttonPath = "";
    ColissionChecker colissionChecker;
    GraphicsLevelEditor graphicsLevelEditor(rendererManager);
    EventsManager eventsManager(&level, &x, &y, &selectedEntityID, &camera, &palette);

    while (!quit)
    {
        if (scroll)
        {
            palette.updatePosition(scrollSpeed);
        }
        graphicsLevelEditor.renderLevel(opacity, buttonPath, camera, level, &palette);

        while (SDL_WaitEventTimeout(&event, WAIT_TIMEOUT))
        {

            if (event.type == SDL_WINDOWEVENT)
            {
                eventsManager.windowsEvent(event, n, quit);
            }
            else
            {
                x = event.motion.x;
                y = event.motion.y;
                SDL_GetMouseState(&x, &y);
                eventsManager.dragSelectedEntity();

                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    scroll = false;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    eventsManager.mouseButtonDown(scroll, scrollSpeed, quit, n, opacity, buttonPath, filename);
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    eventsManager.keyDown(event, quit);
                }
            }
        }

    }
    return n;
}
