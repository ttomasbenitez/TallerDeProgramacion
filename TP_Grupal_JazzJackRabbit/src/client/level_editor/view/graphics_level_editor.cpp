#include "graphics_level_editor.h"
#include "../../../common/sprites_frames.h"
#include "../../../common/enums.h"
#include "../../sprites_path.h"
#include "constants.h"

GraphicsLevelEditor::GraphicsLevelEditor(RendererManager *rendererManager)
{
    this->rendererManager = rendererManager;
}

void GraphicsLevelEditor::renderEntities(LevelData level, Camera camera)
{
    for (auto it = level.entities.begin(); it != level.entities.end(); ++it)
    {
        LevelEntity e = it->second;
        Frame f = e.animation.displayFrame;

        if (e.animation.animationPath != "")
        {
            camera.getRelativePositions(e.x, e.y, e.id);
            rendererManager->copy(e.animation.animationPath, SDL2pp::Rect(f.x, f.y, f.width, f.height), SDL2pp::Rect(e.x, e.y, e.sz.width, e.sz.height));
        }
    }
}
void GraphicsLevelEditor::renderButtons()
{
    Texture *saveButton = rendererManager->getTexture("/save.png");
    rendererManager->copy(saveButton, Rect(0, 0, 720, 360), Rect(WINDOW_WIDTH, 430, 125, 50));
    Texture *returnButton = rendererManager->getTexture("/return.png");
    rendererManager->copy(returnButton, Rect(0, 0, 720, 360), Rect(825, 430, 125, 50));
    Texture *deleteButton = rendererManager->getTexture("/trash.png");
    rendererManager->copy(deleteButton, Rect(0, 0, 720, 360), Rect(950, 430, 50, 50));
}

void GraphicsLevelEditor::renderNotifications(int &opacity, std::string buttonPath)
{
    if (opacity != 0)
    {
        Texture *button = rendererManager->getTexture(buttonPath);
        button->SetBlendMode(SDL_BLENDMODE_BLEND);
        button->SetAlphaMod(opacity);
        rendererManager->copy(button, Rect(0, 0, 720, 360), Rect(230, 410, 250, 50));
        opacity--;
    }
}
void GraphicsLevelEditor::renderBackground(int backgroundID)
{
    Texture *background = rendererManager->getTexture(sprites_path.at((AnimationState)backgroundID));
    rendererManager->copy(background, Rect(0, 0, 720, 360), Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}

void GraphicsLevelEditor::renderLevel(int &opacity, std::string buttonPath, Camera camera, LevelData level, Palette *palette)
{

    rendererManager->clear();

    renderBackground(level.background);
    renderEntities(level, camera);
    palette->showPalette();
    renderButtons();
    renderNotifications(opacity, buttonPath);

    rendererManager->present();
}