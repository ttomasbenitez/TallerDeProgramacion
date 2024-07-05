#ifndef __SCORING_TABLE_H__
#define __SCORING_TABLE_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <vector>
#include "renderer_manager/renderer_manager.h"
#include "music_manager/music_manager.h"
#include "gamestate.h"

struct PlayerInfo
{
    std::string name;
    int points;
};

class ScoringTable
{
private:
    RendererManager *rendererManager;
    MusicManager *musicManager;
    GameState gameState;
    std::vector<PlayerInfo> playersInfo;
    void events();
    void showScoringTable(int scrollPos);

public:
    ScoringTable(RendererManager *rendererManager, MusicManager *musicManager, GameState gameState);
    void initScoringTable();
};

#endif