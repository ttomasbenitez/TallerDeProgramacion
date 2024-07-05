#ifndef COLISSION_CHECKER_H
#define COLISSION_CHECKER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include "level_entities.h"

using namespace SDL2pp;

class ColissionChecker
{
private:
    bool isColliding(LevelEntity &entity, LevelEntity &selectedE, int mouseX, int mouseY);

public:
    bool checkCollision(int mouseX, int mouseY, int selectedID, std::map<int, LevelEntity> &entities);
};

#endif