#ifndef HAZELENGINE_TEXTRENDERER_H
#define HAZELENGINE_TEXTRENDERER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include "Font.h"

class TextRenderer{
public:
    explicit TextRenderer(std::shared_ptr<Font> font);
    GLuint RenderTextToTexture(const std::string &text, SDL_Color color, int &width, int &height);
    void RenderText(const std::string& text, const glm::vec2& position, SDL_Color color);

    void GetTextSize(const std::string& text, int& width, int& height);

private:
    std::shared_ptr<Font> font;
};

#endif