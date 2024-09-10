#include "TextRenderer.h"
#include <iostream>

TextRenderer::TextRenderer(FontManager* fontManager)
        : fontManager(fontManager) {}

void TextRenderer::RenderText(const std::string& text, glm::vec2 position, SDL_Color color){
    int textWidth, textHeight;
    GLuint textTexture = fontManager->RenderTextToTexture(text, color, textWidth, textHeight);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(position.x, position.y);                       // Superior izquierdo
    glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + textWidth, position.y);           // Superior derecho
    glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + textWidth, position.y + textHeight); // Inferior derecho
    glTexCoord2f(0.0f, 1.0f); glVertex2f(position.x, position.y + textHeight);          // Inferior izquierdo
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &textTexture);
}

void TextRenderer::GetTextSize(const std::string& text, int& width, int& height){
    TTF_Font* font = fontManager->GetFont();

    if (font){
        TTF_SizeText(font, text.c_str(), &width, &height);
    }else{
        width = 0;
        height = 0;
    }
}