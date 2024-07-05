#include "camera.h"
#include "constants.h"

Camera::Camera() : view(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) {}

int Camera::getX()
{
    return view.GetX();
}

int Camera::getY()
{
    return view.GetY();
}

int Camera::getWidth()
{
    return WINDOW_WIDTH;
}

int Camera::getHeight()
{
    return WINDOW_HEIGHT;
}

void Camera::moveCamera(int distanceX, int distanceY)
{
    view.x += distanceX;
    view.y += distanceY;
}

void Camera::moveCameraLeft()
{
    if (view.GetX() > 0)
    {
        moveCamera(-CAMERA_SPEED, 0);
    }
}

void Camera::moveCameraRight() { moveCamera(CAMERA_SPEED, 0); }

void Camera::moveCameraUp() { moveCamera(0, -CAMERA_SPEED); }

void Camera::moveCameraDown()
{
    if (view.GetY() < 0)
    {
        moveCamera(0, CAMERA_SPEED);
    }
}

void Camera::getRelativePositions(int &posX, int &posY, AnimationState id)
{
    if (view.GetY() < 0)
    {
        posY = posY - view.GetY();
    }
    posX = posX - view.GetX();
}
