#include "palette.h"
#include "../../../sprites_path.h"
#include "../../../backgrounds.h"
#include "../../../../common/sprites_frames.h"
#include "element_reader.h"
#include "constants.h"

Palette::Palette(RendererManager *rendererManager, int numbOfScenery)
{
    this->rendererManager = rendererManager;
    cameraY = 0;
    int positionX = WINDOW_WIDTH; // 580
    int positionY = 25;
    scrollPos = 0;
    Texture *sprite = rendererManager->getTexture(backgrounds.at(Background::BLACK_SCREEN));
    sprites.push_back(sprite);
    std::vector<Item> items = readItems(numbOfScenery);

    for (int i = 0; i < items.size(); i++)
    {
        Element element;
        element.id = items[i].id;
        element.type = items[i].type;
        element.posX = positionX;
        element.posY = positionY;

        //  Texture& t = rendererManager->getTexture(sprites_path.at((AnimationState)items[i].id));
        // element.Texture& = &(t);

        Texture *sprite = rendererManager->getTexture(sprites_path.at((AnimationState)items[i].id));
        sprites.push_back(sprite);

        positionX += 60;
        // if (positionX >= WINDOW_WIDTH)
        if (positionX >= 1000)
        {
            // positionX = 580;
            positionX = WINDOW_WIDTH;
            positionY += 60;
        }

        palette.push_back(element);
    }
}

std::vector<Item> Palette::readItems(int numbOfScenery)
{
    const char *sceneryItems = DYAML_ARCHIVES "/aiwLevelItems.yaml";
    if (numbOfScenery == 1)
    {
        sceneryItems = DYAML_ARCHIVES "/beachLevelItems.yaml";
    }
    ElementReader elementReader(sceneryItems);
    std::vector<Item> items;
    items.push_back(elementReader.getBackground());
    elementReader.loadElements(items);
    return items;
}

void Palette::showPalette()
{

    rendererManager->copy(sprites[0], Rect(0, 0, 720, 360), Rect(WINDOW_WIDTH, 0, 1000, 480)); // 580 WINDOW_WIDTH
    for (int i = 0; i < palette.size(); i++)
    {
        const Frame frame = animations_frames.at((AnimationState)palette[i].id).at(0);

        rendererManager->copy(sprites[i + 1], Rect(frame.x, frame.y, frame.width, frame.height), Rect(palette[i].posX, palette[i].posY - cameraY, 50, 50));
    }

    // rendererManager->scrollBar(scrollPos);
    if (((palette.size() / 5) * 60) > 340)
    {
        rendererManager->copy("/up.png", Rect(0, 0, 720, 360), Rect(WINDOW_WIDTH, 0, 300, 25));
        rendererManager->copy("/down.png", Rect(0, 0, 720, 360), Rect(WINDOW_WIDTH, 405, 300, 25));
    }
}

std::pair<int, std::string> Palette::selectEntity(int mouseX, int mouseY)
{
    for (int i = 0; i < palette.size(); i++)
    {
        if (mouseX >= palette[i].posX && mouseX <= palette[i].posX + 50 && mouseY >= palette[i].posY - cameraY && mouseY <= palette[i].posY - cameraY + 50)
        {
            return std::make_pair(palette[i].id, palette[i].type);
        }
    }

    return std::make_pair(-1, "");
}

void Palette::updatePosition(int scrollY)
{
    if (((palette.size() / 5) * 60) > 340)
    {
        if (cameraY + scrollY >= 0 && scrollY < 0)
        {
            cameraY += scrollY;
        }
        else if (cameraY + scrollY < 0 && scrollY < 0)
        {
            cameraY = 0;
        }
        else if ((cameraY + scrollY <= ((palette.size() / 5) * 60) - 340 && scrollY > 0))
        {
            cameraY += scrollY;
        }
        else if ((cameraY + scrollY > ((palette.size() / 5) * 60) - 340 && scrollY > 0))
        {
            cameraY = ((palette.size() / 5) * 60) - 340;
        }
        // scrollPos += scrollY;
    }
}