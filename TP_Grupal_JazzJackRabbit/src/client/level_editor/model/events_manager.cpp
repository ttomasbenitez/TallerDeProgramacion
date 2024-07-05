
#include "events_manager.h"
#include "colission_checker.h"
#include "constants.h"

bool EventsManager::inPalette()
{
    return *x >= WINDOW_WIDTH && *y <= 430;
}

EventsManager::EventsManager(LevelData *level, int *x, int *y, int *selectedEntityID, Camera *camera, Palette *palette)
{
    this->x = x;
    this->y = y;
    this->level = level;
    this->selectedEntityID = selectedEntityID;
    this->camera = camera;
    this->palette = palette;
}

void EventsManager::dragSelectedEntity()
{
    if (*selectedEntityID == -1)
    {
        return;
    }
    bool inPalette = *x >= WINDOW_WIDTH && *y <= WINDOW_HEIGHT;
    int posX;
    if (!inPalette)
    {
        posX = *x;
    }
    else if (inPalette)
    {
        posX = WINDOW_WIDTH;
    }

    LevelEntity &e = (level->entities[*selectedEntityID]);

    e.x = posX + camera->getX() - (e.animation.displayFrame.width);
    e.y = *y + camera->getY() - (e.animation.displayFrame.height);
}

void EventsManager::chooseNewEntity()
{
    LevelEntity e;
    std::pair<int, std::string> entityData = palette->selectEntity(*x, *y);
    if (entityData.first != -1 && entityData.second != "background")
    {
        e.id = (AnimationState)entityData.first;
        e.type = entityData.second;
        e.animation.animationPath = sprites_path.at(e.id);
        e.animation.displayFrame = animations_frames.at(e.id).at(0);
        e.x = *x + camera->getX();
        e.y = *y + camera->getY();
        e.sz = entities_sizes.at(e.id);
        e.passability = Passability::IMPASSABLE;
        int newLastElement = 0;
        if (level->entities.begin() != level->entities.end())
        {
            newLastElement = level->entities.rbegin()->first + 1;
        }
        level->entities[newLastElement] = e;
        *selectedEntityID = newLastElement;
    }
    else if (entityData.first != -1 && entityData.second == "background")
    {
        level->background = entityData.first;
    }
}

void EventsManager::scroll(bool &scroll, int &scrollSpeed, int speed)
{
    scroll = true;
    scrollSpeed = speed;
}

void EventsManager::saveGame(int &opacity, std::string &buttonPath, std::string filename)
{
    opacity = 255;
    buttonPath = "/savedSucessfully.png";
    LevelParser parser;
    parser.writeLevelData(filename, *level);
}

int EventsManager::getSelectedEntityID()
{
    std::map<int, LevelEntity>::reverse_iterator it;
    int skipped = -1;
    int mouseY = *y + camera->getY();
    int mouseX = *x + camera->getX();
    for (it = level->entities.rbegin(); it != level->entities.rend(); it++)
    {
        LevelEntity entity = it->second;

        if (mouseX >= entity.x && mouseX <= entity.x + entity.sz.width && mouseY >= entity.y && mouseY <= entity.y + entity.sz.height)
        {
            return it->first;
        }
    }

    return skipped;
}

void EventsManager::mouseButtonDown(bool &scrool, int &scrollSpeed, bool &quit, int &n, int &opacity, std::string &buttonPath, std::string filename)
{
    ColissionChecker colissionChecker;

    if (*x >= 825 && *x < 870 && *y >= 0 && *y <= 25)
    {
        scroll(scrool, scrollSpeed, -2);
    }
    else if (*x >= 825 && *x < 870 && *y >= 405 && *y <= 430)
    {
        scroll(scrool, scrollSpeed, 2);
    }
    else if (inPalette())
    {
        chooseNewEntity();
    }
    else if (*x >= WINDOW_WIDTH && *x < 825 && *y >= 430 && *selectedEntityID == -1)
    {
        saveGame(opacity, buttonPath, filename);
    }
    else if (*x >= 825 && *x < 950 && *y >= 430)
    {
        quit = true;
        n = 0;
    }
    else if (*x >= 950 && *x <= 1000 && *y >= 430)
    {
        if (*selectedEntityID != -1)
        {
            level->entities.erase(*selectedEntityID);
            *selectedEntityID = -1;
        }
    }
    else if (*selectedEntityID != -1)
    {
        //  if (!colissionChecker.checkCollision(*x + camera->getX(), *y + camera->getY(), *selectedEntityID, level->entities))
        //{
        *selectedEntityID = -1;
        // }
        // else
        //{
        //  opacity = 255;
        // buttonPath = "/colission.png";
        //}
    }
    else
    {
        *selectedEntityID = getSelectedEntityID();
    }
}

void EventsManager::keyDown(SDL_Event event, bool &quit)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_q:
        quit = true;

        break;
    case SDLK_LEFT:
        camera->moveCameraLeft();
        break;
    case SDLK_RIGHT:
        camera->moveCameraRight();
        break;
    case SDLK_UP:
        camera->moveCameraUp();
        break;
    case SDLK_DOWN:
        camera->moveCameraDown();
        break;
    default:
        break;
    }
}

void EventsManager::windowsEvent(SDL_Event event, int &n, bool &quit)
{
    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
    {
        quit = true;
        n = -1;
    }
}
