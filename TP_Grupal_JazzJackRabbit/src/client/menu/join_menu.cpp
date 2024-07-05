#include "join_menu.h"
#include "enums.h"
#include "backgrounds.h"
#include <vector>

#include "constants.h"
#include "colors.h"
#include "constant_rate.h"

#define MAX_GAMES_PER_PAGE 5
#define GAMEID games.available_games[i + (page * MAX_GAMES_PER_PAGE)].id
#define CURRENT_PLAYERS games.available_games[i + (page * MAX_GAMES_PER_PAGE)].players_joined
#define MAX_PLAYERS games.available_games[i + (page * MAX_GAMES_PER_PAGE)].players_needed

JoinMenu::JoinMenu(RendererManager *rendererManager, Queue<ClientAction> &actionQueue, Queue<GameState> &responseQueue) : actionQueue(actionQueue), responseQueue(responseQueue)
{
    this->rendererManager = rendererManager;
}

int JoinMenu::join()
{
    bool finished = false;
    int page = 0;

    int offset = 50;
    int fontSize = 25;
    int game = -1;
    ClientAction action(Action::List, 0);
    actionQueue.push(action);
    GameState games;
    loading();
    games = responseQueue.pop();
    // GameState games;
    
    ConstantRateLooper loop(30.0, [&] (int _) {
        rendererManager->clear();
        Texture* background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
        rendererManager->addBackground(background);
        int n = 0;
        std::vector<Rect> buttons;
        for (size_t i = 0; i < MAX_GAMES_PER_PAGE; i++)
        {
            if (games.available_games.empty())
            {
                break;
            }
            if (games.available_games.size() == i + page * MAX_GAMES_PER_PAGE)
            {
                break;
            }
            rendererManager->addText(std::to_string(GAMEID), FONTNAME, fontSize, 30 + 4, VTHIRD + 4 + offset * i, COLOR_BLACK);
            rendererManager->addText(std::to_string(GAMEID), FONTNAME, fontSize, 30, VTHIRD + offset * i, COLOR_WHITE);
            rendererManager->addText(std::to_string(CURRENT_PLAYERS), FONTNAME, fontSize, VWIDTH + 4, VTHIRD + 4 + offset * i, COLOR_BLACK);
            rendererManager->addText(std::to_string(CURRENT_PLAYERS), FONTNAME, fontSize, VWIDTH, VTHIRD + offset * i, COLOR_WHITE);
            rendererManager->addText(std::to_string(MAX_PLAYERS), FONTNAME, fontSize, VWIDTH + 35 + 4, VTHIRD + 4 + offset * i, COLOR_BLACK);
            rendererManager->addText(std::to_string(MAX_PLAYERS), FONTNAME, fontSize, VWIDTH + 35, VTHIRD + offset * i, COLOR_WHITE);
            rendererManager->addText("Join", FONTNAME, fontSize, 600 + 4, VTHIRD + 4 + offset * i, COLOR_BLACK);
            buttons.push_back(rendererManager->addText("Join", FONTNAME, fontSize, 600, VTHIRD + offset * i, COLOR_WHITE));
            n += 1;
        }
        buttons.push_back(rendererManager->addText("RETURN", FONTNAME, 40, VWIDTH + 4, VTHIRD + 4 + offset * MAX_GAMES_PER_PAGE, COLOR_BLACK));
        rendererManager->addText("RETURN", FONTNAME, 40, VWIDTH, VTHIRD + offset * MAX_GAMES_PER_PAGE, COLOR_WHITE);
        if (page != 0)
        {
            buttons.push_back(rendererManager->addText("<-", FONTNAME, 40, 50, VTHIRD + 4 + offset * MAX_GAMES_PER_PAGE, COLOR_WHITE));
        }
        buttons.push_back(rendererManager->addText("->", FONTNAME, 40, 600, VTHIRD + offset * MAX_GAMES_PER_PAGE, COLOR_WHITE));
        rendererManager->present();
        int index = event(finished, page, n, buttons);
        if (index >= 0)
        {
            game = index + page * MAX_GAMES_PER_PAGE;
        }
        else
        {
            game = -1;
        }
        return !finished;
    });
    loop.run();
    if (game == -1)
    {
        return -1;
    }
    return games.available_games[game].id;
}

int JoinMenu::event(bool &finished, int &page, int n, std::vector<Rect> buttons)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                finished = true;
                return -1;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            Rect mouse = {event.motion.x, event.motion.y, 10, 10};
            for (size_t i = 0; i < n; i++)
            {

                if (mouse.Intersects(buttons[i]))
                {
                    finished = true;
                    return i;
                }
            }
            if (mouse.Intersects(buttons[n]))
            {
                finished = true;
                return -1;
            }
            if (mouse.Intersects(buttons[n + 1]))
            {
                if (page > 0)
                {
                    page = page - 1;
                }
                return 0;
            }
            if (mouse.Intersects(buttons[n + 2]))
            {
                if (n > 1)
                {
                    page++;
                }
                return 0;
            }
        }
    }
    return -1;
}

void JoinMenu::loading()
{

    Texture* background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);
    rendererManager->addText("LOADING...", FONTNAME, 40, VWIDTH, VTHIRD + 4 + 80, COLOR_BLACK);
    rendererManager->addText("LOADING...", FONTNAME, 40, VWIDTH, VTHIRD + 80, COLOR_WHITE);
    rendererManager->present();
}