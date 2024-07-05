#ifndef __RENDERE_MANAGER_H__
#define __RENDERE_MANAGER_H__

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <unordered_map>
#include <memory>

class RendererManager
{
private:
    Renderer *renderer;
    std::unordered_map<std::string, std::unique_ptr<Texture>> texture_cache;
    std::unordered_map<std::string, std::unique_ptr<Font>> font_cache;
    Texture getTextTexture(std::string text, std::string FONTNAME, int fontSize, SDL_Color color);
    std::string wrapTextByLetter(const std::string &text, Font& font, int wrapWidth, int pos, int &cursorPos);
    Texture getTextTextureWrapped(std::string text, std::string FONTNAME, int fontSize, SDL_Color color, int wrapWidth, int pos, int &cursorPos);

public:
    void clear();
    void copy(std::string imagePath, Rect image, Rect target);
    void copy(Texture* sprite, Rect image, Rect target);
    void copy(Texture* sprite, Rect image, Rect target, int flip);
    void addBackground(Texture* background);
    Rect addText(std::string text, std::string FONTNAME, int fontSize, int posX, int posY, SDL_Color color);
    Rect addTextBackground(std::string text, std::string FONTNAME, int fontSize, int posX, int posY, SDL_Color color, int pos, bool showCursor);
    Texture* getTexture(std::string imagePath);
    void scrollBar(int pos, int contentHeight, int windowHeight);
    void present();

    RendererManager(Renderer *renderer);
};

#endif