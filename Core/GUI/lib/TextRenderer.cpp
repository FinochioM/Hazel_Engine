#include "TextRenderer.h"
#include <iostream>


TextRenderer::TextRenderer(std::shared_ptr<Font> font)
        : font(font) {}

void TextRenderer::RenderText(const std::string &text, const glm::vec2 &position, SDL_Color color){
    int width, height;
    GLuint textTexture = RenderTextToTexture(text, color, width, height);
    if (textTexture == 0){
        std::cerr << "Failed to render text to texture." << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textTexture);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Asegurar color blanco con opacidad completa

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(position.x, position.y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + width, position.y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + width, position.y + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(position.x, position.y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &textTexture);
}

GLuint TextRenderer::RenderTextToTexture(const std::string &text, SDL_Color color, int &width, int &height){
    SDL_Surface* originalSurface = TTF_RenderText_Blended(font->GetFont(), text.c_str(), color);
    if (!originalSurface) {
        std::cerr << "Error al renderizar el texto: " << TTF_GetError() << std::endl;
        return 0;
    }

    // Convertir la superficie a RGBA8888
    SDL_Surface* textSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_RGBA8888, 0);
    if (!textSurface) {
        std::cerr << "Error al convertir la superficie: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(originalSurface);
        return 0;
    }

    width = textSurface->w;
    height = textSurface->h;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Usar GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    SDL_FreeSurface(originalSurface);
    SDL_FreeSurface(textSurface);

    return textureID;
}

void TextRenderer::GetTextSize(const std::string& text, int& width, int& height){
    if (!font || !font->GetFont()) {
        width = 0;
        height = 0;
        return;
    }

    TTF_SizeText(font->GetFont(), text.c_str(), &width, &height);
}