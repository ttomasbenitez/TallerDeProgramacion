#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2pp/SDL2pp.hh>
#include "../../../common/enums.h"

#define CAMERA_SPEED 10
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 480

class Camera
{
private:
    SDL2pp::Rect view;
    void moveCamera(int distanceX, int distanceY);

public:
    Camera();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void getRelativePositions(int &posX, int &posY, AnimationState type);
    void moveCameraLeft();
    void moveCameraRight();
    void moveCameraUp();
    void moveCameraDown();
    ~Camera() = default;
};

#endif // CAMERA_H
