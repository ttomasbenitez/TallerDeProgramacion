
#include "colission_checker.h"
bool ColissionChecker::isColliding(LevelEntity &entity, LevelEntity &selectedE, int mouseX, int mouseY)
{

    if (entity.id == BEACH_RISE)
    {
        Rect hitbox(entity.x, entity.y, entity.sz.width, entity.sz.height);
        if (hitbox.Intersects(Rect(mouseX, mouseY, selectedE.sz.width, selectedE.sz.height)))
        {

            // Verificar que selectedE está a la derecha del borde izquierdo de entity
            if (mouseX >= entity.x)
            {
                // pendiente del triángulo
                float slope = entity.sz.height / entity.sz.width;

                // valor y en la línea del triángulo para la x de selectedE
                float triangleY = entity.y + entity.sz.height - slope * (mouseX - entity.x);

                // Verificar si el punto superior de selectedE está debajo de la línea del triángulo
                return (mouseY > triangleY && mouseY <= triangleY + 80);
            }
        }
    }
    else if (entity.id == BEACH_DESCENT)
    {
        Rect hitbox(entity.x, entity.y, entity.sz.width, entity.sz.height);
        if (hitbox.Intersects(Rect(mouseX, mouseY, selectedE.sz.width, selectedE.sz.height)))
        {
            if (mouseX >= entity.x)
            {
                float slope = -(entity.sz.height / entity.sz.width);
                float triangleY = entity.y - slope * (mouseX - entity.x);

                return (mouseY > triangleY && mouseY <= triangleY + 80);
            }
        }
    }
    else if (entity.id == BEACH_FLOATING_FLOOR)
    {
        return (mouseX >= entity.x && mouseX <= entity.x + entity.sz.width && mouseY >= (entity.y + 10) && mouseY <= (entity.y + 10) + (entity.sz.height - 10));
    }
    else
    {
        return (mouseX >= entity.x && mouseX <= entity.x + entity.sz.width && mouseY >= entity.y && mouseY <= entity.y + entity.sz.height);
    }
    return false;
}

bool ColissionChecker::checkCollision(int mouseX, int mouseY, int selectedID, std::map<int, LevelEntity> &entities)
{
    AnimationState sID = entities[selectedID].id;

    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        LevelEntity &e = it->second;

        if (it->first != selectedID && (sID == e.id || e.passability == IMPASSABLE))
        {
            if (isColliding(e, entities[selectedID], mouseX, mouseY))
            {
                return true;
            }
        }
    }
    return false;
}
