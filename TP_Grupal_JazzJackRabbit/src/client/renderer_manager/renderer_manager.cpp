#include "renderer_manager.h"

RendererManager::RendererManager(Renderer *renderer)
{
    this->renderer = renderer;
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
}

void RendererManager::copy(std::string imagePath, Rect image, Rect target)
{
    renderer->Copy(
        *getTexture(imagePath),
        image,
        target);
}

void RendererManager::copy(Texture* sprite, Rect image, Rect target)
{
    renderer->Copy(
        *sprite,
        image,
        target);
}

void RendererManager::copy(Texture* sprite, Rect image, Rect target, int flip)
{
    if (flip == -1)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }
    const Optional<Point> angle;

    renderer->Copy(
        *sprite,
        image,
        target, (double)0, angle, flip);
}

void RendererManager::addBackground(Texture* background)
{
    renderer->Copy(*background);
}

Rect RendererManager::addText(std::string text, std::string FONTNAME, int fontSize, int posX, int posY, SDL_Color color)
{
    Texture text_sprite = getTextTexture(text, FONTNAME, fontSize, color);
    renderer->Copy(text_sprite, NullOpt, Rect(posX, posY, text_sprite.GetWidth(), text_sprite.GetHeight()));
    return Rect(posX, posY, text_sprite.GetWidth(), text_sprite.GetHeight());
}

Texture RendererManager::getTextTexture(std::string text, std::string FONTNAME, int fontSize, SDL_Color color)
{
    SDLTTF ttf;

    Font font(DATA_PATH + FONTNAME, fontSize);
    Texture text_sprite(
        *renderer,
        font.RenderText_Solid(text, color));
    return text_sprite;
}

Texture RendererManager::getTextTextureWrapped(std::string text, std::string FONTNAME, int fontSize, SDL_Color color, int wrapWidth, int pos, int &cursorPos)
{
    SDLTTF ttf;
    std::string wrappedText = " ";
    auto path = DATA_PATH + FONTNAME;
    /*
    auto fontID = path + std::to_string(fontSize);
    if (!font_cache.count(fontID)) {
        font_cache[fontID] = std::make_unique<Font>(path, fontSize);
    }
    Font& font = *font_cache[fontID];
    */
    Font font(path, fontSize);
    if (text != "")
    {
        wrappedText = wrapTextByLetter(text, font, wrapWidth, pos, cursorPos);
    }

    Texture text_sprite(
        *renderer,
        font.RenderText_Solid(wrappedText, color));
    return text_sprite;
}

void RendererManager::scrollBar(int scrollPos, int contentHeight, int windowHeight)
{
    renderer->SetDrawColor(209, 209, 209);
    renderer->FillRect(0, 0, 15, windowHeight);
    renderer->SetDrawColor(179, 179, 179);
    float thumbHeight = (windowHeight * windowHeight) / (float)contentHeight;
    float thumbPosY = ((scrollPos) * (windowHeight - thumbHeight)) / (float)(contentHeight - windowHeight);
    renderer->FillRect(0, thumbPosY, 15, thumbHeight + thumbPosY);
}

std::string RendererManager::wrapTextByLetter(const std::string &text, Font& font, int wrapWidth, int pos, int &cursorPos)
{
    std::string line;
    int lineWidth = 0;
    int initialPos = pos;

    std::string mutableText = text;

    std::string::iterator it = mutableText.begin() + pos;
    std::string::reverse_iterator rit(it);

    while (rit != mutableText.rend())
    {
        int minx, maxx, miny, maxy, charWidth;

        font.GetGlyphMetrics(*rit, minx, maxx, miny, maxy, charWidth);

        if (lineWidth + charWidth > wrapWidth)
        {
            cursorPos = lineWidth;
            std::reverse(line.begin(), line.end());
            return line;
        }

        initialPos--;
        lineWidth += charWidth;
        line += *rit;
        ++rit;
    }
    cursorPos = lineWidth;

    std::reverse(line.begin(), line.end());

    while (it != mutableText.end())
    {
        int minx, maxx, miny, maxy, charWidth;

        font.GetGlyphMetrics(*it, minx, maxx, miny, maxy, charWidth);

        if (lineWidth + charWidth > wrapWidth)
        {
            return line;
        }
        initialPos--;
        lineWidth += charWidth;
        line += *it;
        ++it;
    }
    return line;
}

Rect RendererManager::addTextBackground(std::string text, std::string FONTNAME, int fontSize, int posX, int posY, SDL_Color color, int pos, bool showCursor)
{
    int cursorPos = 0;
    Texture text_sprite = getTextTextureWrapped(text, FONTNAME, fontSize, color, 340, pos, cursorPos);
    Texture* input = getTexture("/input.png");
    renderer->Copy(*input, NullOpt, Rect(posX - 10, posY, 350, text_sprite.GetHeight()));
    renderer->Copy(text_sprite, NullOpt, Rect(posX, posY, text_sprite.GetWidth(), text_sprite.GetHeight()));
    if (showCursor)
    {
        renderer->SetDrawColor(128, 0, 255);
        renderer->DrawLine(posX + cursorPos, posY + 10, posX + cursorPos, posY + 40);
    }

    return Rect(posX, posY, text_sprite.GetWidth(), text_sprite.GetHeight());
}

Texture* RendererManager::getTexture(std::string imagePath)
{
    auto path = DATA_PATH + imagePath;
    if (!texture_cache.count(path)) {
        texture_cache[path] = std::make_unique<Texture>(*renderer, path);
    }
    return &*texture_cache[path];
}

void RendererManager::present()
{

    renderer->Present();
}

void RendererManager::clear()
{
    renderer->Clear();
}