#ifndef __GAME_INFORMATION_H__
#define __GAME_INFORMATION_H__
#include <string>
struct gameInformation
{
    int characterId;
    int gameId;
    bool hasCreatedGame;
    std::string name;
    int gun;
    std::string mapPath;
};
#endif