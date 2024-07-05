#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include "thread.h"
#include "queue.h"
#include "renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"
#include "clientaction.h"
#include "gamestate.h"
#include <SDL2pp/SDL.hh>
#include "game_information.h"

using namespace SDL2pp;
class Client;

class Graphics : public Thread
{
private:
    Queue<GameState> &responseQueue;
    Queue<ClientAction> &queueActions;
    SDL sdl;
    int clientID;
    Client &client;
    Mixer mixer;
    MusicManager musicManager;
    void renderEntity(RenderableGameEntity entity, Rect camera, RendererManager *rendererManager);
    void loading(RendererManager *rendererManager);
    void connectionLost(RendererManager *rendererManager);
    // Window window;
    // Renderer renderer;

public:
    Graphics(Queue<GameState> &queue, Queue<ClientAction> &queueActions, Client &client);
    void draw(GameState response, RendererManager *rendererManager, MusicManager *musicManager);
    bool initScreen(RendererManager *rendererManager, Window *window, MusicManager *musicManager);
    void run() override;
    void stop() override;
    ~Graphics() = default;
};

#endif