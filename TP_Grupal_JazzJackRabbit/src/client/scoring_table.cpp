#include "scoring_table.h"
#include "backgrounds.h"
#include "constants.h"
#include "colors.h"
#include "constant_rate.h"
bool compareByValue(const PlayerInfo a, const PlayerInfo b)
{
    return a.points > b.points;
}
ScoringTable::ScoringTable(RendererManager *rendererManager, MusicManager *musicManager, GameState gameState)
{
    this->rendererManager = rendererManager;
    this->musicManager = musicManager;
    this->gameState = gameState;
    for (Player player : gameState.players)
    {
        PlayerInfo playerInfo = {player.name,
                                 player.points};
        auto it = std::lower_bound(playersInfo.begin(), playersInfo.end(), playerInfo, compareByValue);
        playersInfo.insert(it, playerInfo);
    }
}

void ScoringTable::events()
{
    int scrollPos = 0;
    bool hasClosed = false;
    bool drag = false;
    int contentHeight = 78 + playersInfo.size() * 30;
    SDL_Event event;
    ConstantRateLooper loop(30.0, [&](int _)
                            {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    hasClosed = true;
                }
            }
            else
            {
                if (drag)
                {
                    int mouseY;
                    SDL_GetMouseState(NULL, &mouseY);
                    scrollPos = mouseY;
                    showScoringTable(scrollPos);
                }
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = event.motion.x;
                    if (x <= 15)
                    {
                        drag = true;
                    }
                }
                else if (event.type == SDL_MOUSEBUTTONUP)
                {
                    drag = false;
                }
                else if (event.type == SDL_MOUSEWHEEL)
                {
                    if (contentHeight > WINDOW_HEIGHT)
                    {
                        if (event.wheel.y > 0)
                        {
                            scrollPos -= 10;
                            if (scrollPos < 0)
                                scrollPos = 0;
                        }
                        else if (event.wheel.y < 0)
                        {
                            scrollPos += 10;
                            if (scrollPos > contentHeight - WINDOW_HEIGHT)
                                scrollPos = contentHeight - WINDOW_HEIGHT;
                        }
                        showScoringTable(scrollPos);
                    }
                }
            }
        }
        return !hasClosed; });
    loop.run();
}

void ScoringTable::initScoringTable()
{
    showScoringTable(0);
    events();
}

void ScoringTable::showScoringTable(int scrollPos)
{
    rendererManager->clear();
    int contentHeight = 78 + playersInfo.size() * 30;
    int viewportHeight = WINDOW_HEIGHT;
    int thumbHeight = (WINDOW_HEIGHT * WINDOW_HEIGHT) / (float)contentHeight;
    int thumbPosY = ((scrollPos) * (WINDOW_HEIGHT - thumbHeight)) / (float)(contentHeight - WINDOW_HEIGHT);
    int maxScrollPos = contentHeight - viewportHeight;
    int contentPos = (thumbPosY * maxScrollPos) / (viewportHeight - thumbHeight);

    Texture *background = rendererManager->getTexture(backgrounds.at(Background::GENERAL_SCREEN));
    rendererManager->addBackground(background);

    rendererManager->addText("Score table", FONTNAME, 40, 200 + 4, 0 + 4 - contentPos, COLOR_BLACK);
    Rect scoreTable = rendererManager->addText("Score table", FONTNAME, 40, 200, 0 - contentPos, COLOR_WHITE);

    int hwidthPos = 30;
    int hwidthName = 50;
    int hwidthPoints = 350;
    int posYTable = scoreTable.GetH();
    int fontSize = 25;

    Rect pos = rendererManager->addText("Pos", FONTNAME, fontSize, hwidthPos + 4, posYTable + 4 - contentPos, COLOR_BLACK);
    Rect score = rendererManager->addText("Name", FONTNAME, fontSize, pos.GetW() + hwidthName + 4, posYTable + 4 - contentPos, COLOR_BLACK);
    rendererManager->addText("Score", FONTNAME, fontSize, score.GetW() + pos.GetW() + hwidthName + hwidthPoints + 4, posYTable + 4 - contentPos, COLOR_BLACK);

    Rect pos2 = rendererManager->addText("Pos", FONTNAME, fontSize, hwidthPos, posYTable - contentPos, COLOR_WHITE);
    Rect score2 = rendererManager->addText("Name", FONTNAME, fontSize, pos2.GetW() + hwidthName, posYTable - contentPos, COLOR_WHITE);
    rendererManager->addText("Score", FONTNAME, fontSize, score2.GetW() + pos2.GetW() + hwidthName + hwidthPoints, posYTable - contentPos, COLOR_WHITE);

    if (contentHeight > WINDOW_HEIGHT)
    {
        rendererManager->scrollBar(scrollPos, scoreTable.GetH() + score2.GetH() + playersInfo.size() * 30, WINDOW_HEIGHT);
    }
    int posY = 0;

    for (int i = 0; i < playersInfo.size(); i++)
    {
        int height = posYTable + score.GetH() + posY;
        posY += 30;
        if (contentPos <= height)
        {
            rendererManager->addText(std::to_string(i), FONTNAME, 15, hwidthName + 4, height - contentPos + 4, COLOR_BLACK);
            rendererManager->addText(std::to_string(i), FONTNAME, 15, hwidthName + 4, height - contentPos, COLOR_WHITE);

            rendererManager->addText(playersInfo[i].name, FONTNAME, 15, pos.GetW() + hwidthName + 4, height - contentPos + 4, COLOR_BLACK);
            rendererManager->addText(playersInfo[i].name, FONTNAME, 15, pos.GetW() + hwidthName + 4, height - contentPos, COLOR_WHITE);
            std::string points = std::to_string(playersInfo[i].points);
            rendererManager->addText(points, FONTNAME, 15, score.GetW() + pos.GetW() + hwidthName + hwidthPoints + 4, height - contentPos + 4, COLOR_BLACK);
            rendererManager->addText(points, FONTNAME, 15, score.GetW() + pos.GetW() + hwidthName + hwidthPoints + 4, height - contentPos, COLOR_WHITE);
        }
    }
    rendererManager->present();
}
