#include "graphics.h"
#include "choose/choose_characters.h"
#include "choose/choose_scenery.h"
#include "menu/menu.h"
#include "actions.h"
#include "sprites_frames.h"
#include "sprites_path.h"
#include "backgrounds.h"
#include "entities_sizes.h"
#include "sprites_path.h"
#include "scoring_table.h"
#include "constants.h"
#include "colors.h"
#include "client.h"

#include <iostream>

#define CONVERSION_ALTURA WINDOW_HEIGHT / 16
#define CONVERSION_LONGITUD WINDOW_WIDTH / 16

Graphics::Graphics(Queue<GameState> &queue, Queue<ClientAction> &queueActions, Client &client) : responseQueue(queue), queueActions(queueActions),
                                                                                                 sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), client(client), mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
                                                                                                 musicManager(&mixer)
{
}

void Graphics::run()
{
    Window window("JazzJack Rabbit 2",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  WINDOW_WIDTH, WINDOW_HEIGHT,
                  SDL_WINDOW_SHOWN);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    RendererManager rendererManager(&renderer);
    // Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    // MusicManager musicManager(&mixer);

    ClientAction action(Action::List, 0);
    queueActions.push(action);
    GameState response = responseQueue.pop();
    clientID = response.clientID;

    if (initScreen(&rendererManager, &window, &musicManager))
    {
        SDL_SetWindowSize(window.Get(), 1000, WINDOW_HEIGHT);

        // la thread actionHandler se deberia activar una vez que el cliente ya entro en una partida
        Actions actionHandler(queueActions);
        actionHandler.start();
        loading(&rendererManager);
        GameState state;
        musicManager.stopMusic();
        musicManager.playLevelMusic();
        while (actionHandler.is_Running())
        {
            try
            {
                state = responseQueue.pop();
                if (state.type == MsgType::GameState)
                {
                    draw(state, &rendererManager, &musicManager);
                }
            }
            catch (const ClosedQueue &e)
            {
                break;
            }
        }
        SDL_SetWindowSize(window.Get(), WINDOW_WIDTH, WINDOW_HEIGHT);
        musicManager.stopMusic();

        ScoringTable scoringTable(&rendererManager, &musicManager, state);
        scoringTable.initScoringTable();
        actionHandler.stop();
        actionHandler.join();
    }
    else
    {
        try
        {
            ClientAction action(Action::Quit, 0);
            queueActions.push(action);
        }
        catch (const ClosedQueue &e)
        {
        }
    }
    _is_alive = false;
    client.notify_exit();
}

bool Graphics::initScreen(RendererManager *rendererManager, Window *window, MusicManager *musicManager)
{
    musicManager->playMenuMusic();
    Texture *background = rendererManager->getTexture(backgrounds.at(Background::INIT_SCREEN));
    rendererManager->addBackground(background);

    // Show rendered frame
    rendererManager->present();

    SDL_Delay(1000);

    gameInformation game;
    game.characterId = -1;
    game.gameId = -1;
    game.hasCreatedGame = false;

    Menu menu(rendererManager, musicManager, queueActions, responseQueue);
    menu.initMenu(game, window);
    AnimationState characterID;
    if (game.characterId == 0)
        characterID = JAZZ;
    if (game.characterId == 2)
        characterID = LORI;
    if (game.characterId == 1)
        characterID = SPAZ;
    try
    {
        if (game.hasCreatedGame && game.characterId != -1)
        {
            ClientAction action(Action::Create, characterID, game.name, game.mapPath);
            queueActions.push(action);
            return true;
        }
        else if (!game.hasCreatedGame && game.characterId != -1 && game.gameId != -1)
        {
            ClientAction action(Action::Join, game.gameId, characterID, game.name);
            queueActions.push(action);
            return true;
        }
    }
    catch (const ClosedQueue &e)
    {
        connectionLost(rendererManager);
    }
    return false;
}

void Graphics::draw(GameState response, RendererManager *rendererManager, MusicManager *musicManager)
{
    SDLTTF ttf;
    // Font font();
    Rect camera(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Texture *background = rendererManager->getTexture(sprites_path.at((AnimationState)response.background));
    rendererManager->addBackground(background);
    // Set camera to follow the client's player
    Player *mainPlayer; //= response.players.at(clientID);
    for (Player &player : response.players)
    {
        if (player.id == clientID)
        {
            mainPlayer = &player;
            break;
        }
    }
    Frame mainPlayerFrame = animations_frames.at((AnimationState)mainPlayer->entity.animation_state).at(mainPlayer->entity.animation_tick);
    camera.SetX(mainPlayer->entity.x /** CONVERSION_LONGITUD*/ + /*mainPlayerFrame.x / 2*/ -WINDOW_WIDTH / 2);
    camera.SetY((mainPlayer->entity.y) /** CONVERSION_ALTURA*/ + /*mainPlayerFrame.y / 2*/ -WINDOW_HEIGHT / 2);
    for (RenderableGameEntity entity : response.entities)
    {
        if (!musicManager->playSound((AnimationState)entity.animation_state))
        {
            renderEntity(entity, camera, rendererManager);
        }
    }
    std::vector<int> points({0, 0, 0});
    for (Player &player : response.players)
    {
        musicManager->playSound((AnimationState)player.entity.animation_state);
        auto it = std::lower_bound(points.begin(), points.end(), player.points, std::greater<int>());
        points.insert(it, player.points);
        renderEntity(player.entity, camera, rendererManager);
    }

    int fontSize = 25;
    rendererManager->addText(std::to_string(response.sec_left), FONTNAME, fontSize, WINDOW_WIDTH / 2, 0, COLOR_WHITE);
    rendererManager->addText(std::to_string(mainPlayer->points), FONTNAME, fontSize, fontSize * 2, WINDOW_HEIGHT - fontSize * 2, COLOR_YELLOW);
    rendererManager->addText(std::to_string(mainPlayer->health), FONTNAME, fontSize, WINDOW_WIDTH - fontSize * 2, WINDOW_HEIGHT - fontSize * 2, COLOR_RED);
    Texture *backgroundTop = rendererManager->getTexture(backgrounds.at(Background::BLACK_SCREEN));
    rendererManager->copy(backgroundTop, Rect(0, 0, 720, 360), Rect(WINDOW_WIDTH, 0, 1000, WINDOW_HEIGHT)); // 580 WINDOW_WIDTH

    Rect top = rendererManager->addText("TOP 3: ", FONTNAME, fontSize, WINDOW_WIDTH, 0, COLOR_WHITE);
    Rect first = rendererManager->addText("1st: " + std::to_string(points[0]), FONTNAME, fontSize, WINDOW_WIDTH, 0 + top.GetH(), COLOR_WHITE);
    Rect second = rendererManager->addText("2nd: " + std::to_string(points[1]), FONTNAME, fontSize, WINDOW_WIDTH, 0 + top.GetH() + first.GetH(), COLOR_WHITE);
    Rect third = rendererManager->addText("3rd: " + std::to_string(points[2]), FONTNAME, fontSize, WINDOW_WIDTH, 0 + top.GetH() + first.GetH() + second.GetH(), COLOR_WHITE);

    Texture *guns = rendererManager->getTexture("/guns.png");

    Frame frameGuns;
    if (mainPlayer->bulletType == SHOT_RED_ROCKET)
    {
        frameGuns = gun_position.at((Guns)2);
    }
    else if (mainPlayer->bulletType == SHOT_FIREBALL)

    {
        frameGuns = gun_position.at((Guns)(1));
    }
    else
    {
        frameGuns = gun_position.at((Guns)(0));
    }
    std::string ammo;
    if (mainPlayer->currentAmmo == -1)
    {
        ammo = "Infinite";
    }
    else
    {
        ammo = std::to_string(mainPlayer->currentAmmo);
    }

    rendererManager->copy(guns, Rect(frameGuns.x, frameGuns.y, frameGuns.width, frameGuns.height), Rect(WINDOW_WIDTH, 430, 50, 50));
    rendererManager->addText("x " + ammo, FONTNAME, 35, 755, 440, COLOR_WHITE);
    rendererManager->present();
}

void Graphics::renderEntity(RenderableGameEntity entity, Rect camera, RendererManager *rendererManager)
{
    int sizeX = entities_sizes.at((AnimationState)entity.entity).width;
    int sizeY = entities_sizes.at((AnimationState)entity.entity).height;
    std::string path = sprites_path.at((AnimationState)entity.animation_state);
    Texture *sprite = rendererManager->getTexture(path);
    const Frame frame = animations_frames.at((AnimationState)entity.animation_state).at(entity.animation_tick);

    rendererManager->copy(sprite, Rect(frame.x, frame.y, frame.width, frame.height), Rect(entity.x /* CONVERSION_LONGITUD*/ - camera.GetX(), (entity.y /** CONVERSION_ALTURA*/ - camera.GetY()), sizeX, sizeY), entity.direction);
}

void Graphics::loading(RendererManager *rendererManager)
{

    Texture *background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);
    rendererManager->addText("WATING FOR PLAYERS...", FONTNAME, 40, 50, WINDOW_HEIGHT / 2, COLOR_WHITE);
    rendererManager->present();
}

void Graphics::connectionLost(RendererManager *rendererManager)
{

    Texture *background = rendererManager->getTexture(backgrounds.at(Background::MAIN_SCREEN));
    rendererManager->addBackground(background);
    rendererManager->addText("No connection Shuting down", FONTNAME, 40, 0, WINDOW_HEIGHT / 2, COLOR_WHITE);
    rendererManager->present();
    SDL_Delay(1000);
}

void Graphics::stop()
{
    _is_alive = false;
    _keep_running = false;
}