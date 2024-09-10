#ifndef HAZELENGINE_TEXTRENDERER_H
#define HAZELENGINE_TEXTRENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "FontManager.h"

class TextRenderer{
public:
    explicit TextRenderer(FontManager* fontManager);
    void RenderText(const std::string& text, glm::vec2 position, SDL_Color color);

    void GetTextSize(const std::string& text, int& width, int& height);

private:
    FontManager* fontManager;
};

#endif