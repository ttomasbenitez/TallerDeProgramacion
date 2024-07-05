#include "../../common/mapsParser/map.h"
#include "../../common/mapsParser/mapsParser.h"
#include "../backgrounds.h"
#include "colors.h"
#include "constant_rate.h"
#include "constants.h"
#include "maps_menu.h"

MapsMenu::MapsMenu(RendererManager *rendererManager,
                   MusicManager *musicManager)
{
  this->rendererManager = rendererManager;
  this->musicManager = musicManager;
  cameraY = 0;

  std::vector<mapData> maps;
  MapsParser mapsParser(DYAML_ARCHIVES "/maps.yaml");
  mapsParser.getMaps(maps);
  int positionY = 50;

  for (int i = 0; i < maps.size(); i++)
  {
    mapElement element;
    element.path = maps[i].path;
    element.name = maps[i].name;
    element.posY = positionY;
    positionY += 50;
    mapElements.push_back(element);
  }
}

std::string MapsMenu::selectMap(int mouseX, int mouseY)
{
  for (int i = 0; i < mapElements.size(); i++)
  {
    if (mouseX >= 200 && mouseX <= 200 + mapElements[i].width &&
        mouseY >= mapElements[i].posY &&
        mouseY <= mapElements[i].posY + mapElements[i].height)
    {

      return mapElements[i].path;
    }
  }

  return "";
}
void MapsMenu::setCameraPos(int scrollSpeed)
{
  if (scrollSpeed > 0)
  {
    if (mapElements.size() * 50 + 50 > cameraY + 430)
    {
      cameraY += scrollSpeed;
    }
  }
  else
  {
    if (cameraY > 0)
    {
      cameraY += scrollSpeed;
    }
  }
}
std::string MapsMenu::events()
{
  bool hasClosed = false;
  bool scroll = false;
  int scrollSpeed = 0;
  SDL_Event event;
  std::string ret("");
  showMenuGames();
  ConstantRateLooper loop(30.0, [&](int _)
                          {
    if (scroll) {
      setCameraPos(scrollSpeed);
      showMenuGames();
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          return false;
        }
      } else {

        int x = event.motion.x;
        int y = event.motion.y;

        if (event.type == SDL_MOUSEBUTTONUP) {
          scroll = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
          if (mapElements.size() * 50 + 50 > WINDOW_HEIGHT) {
            if (y <= 50) {
              scroll = true;
              scrollSpeed = -50;
            } else if (y >= 430) {
              scroll = true;
              scrollSpeed = 50;
            }
          }
          if (!scroll) {
            std::string filename = selectMap(x, y + cameraY);
            if (filename != "") {
              ret = DYAML_ARCHIVES + filename;
              return false;
            }
          }
        }
      }
    }
    return !hasClosed; });
  loop.run();
  return ret;
}

void MapsMenu::showMenuGames()
{
  rendererManager->clear();

  Texture *background =
      rendererManager->getTexture(backgrounds.at(Background::GENERAL_SCREEN));
  rendererManager->addBackground(background);

  int wPos = 200;

  for (int i = 0; i < mapElements.size(); i++)
  {
    Rect r = rendererManager->addText(
        mapElements[i].name, FONTNAME, 40, wPos + 4,
        mapElements[i].posY + 4 - cameraY, COLOR_BLACK);
    mapElements[i].width = r.GetW();
    mapElements[i].height = r.GetH();
    rendererManager->addText(mapElements[i].name, FONTNAME, 40, wPos,
                             mapElements[i].posY - cameraY, COLOR_WHITE);
  }

  if (mapElements.size() * 50 + 50 > WINDOW_HEIGHT)
  {
    rendererManager->copy("/up.png", Rect(0, 0, 300, 25),
                          Rect(0, 0, WINDOW_WIDTH, 50));
    rendererManager->copy("/down.png", Rect(0, 0, 300, 25),
                          Rect(0, 430, WINDOW_WIDTH, 50));
  }

  rendererManager->present();
}

std::string MapsMenu::initMenu() { return events(); }
