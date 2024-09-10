#include "Button.h"
#include <GL/glew.h>
#include <iostream>

Button::Button(const glm::vec2& position, const glm::vec2& size, const std::string& text, TextRenderer* textRenderer)
        : Widget(position, size, textRenderer), Node("ButtonNode"), text(text) {
}

void Button::Render(){
    if (!isVisible) return;

    glEnable(GL_BLEND);

    glColor3f(0.0f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + size.x, position.y);
        glVertex2f(position.x + size.x, position.y + size.y);
        glVertex2f(position.x, position.y + size.y);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    SDL_Color textColor = {(Uint8) 255, (Uint8) 255, (Uint8) 255, (Uint8) 255};
    RenderTextCentered(text, textColor);
}

void Button::Update(float deltaTime) {}

void Button::SetText(const std::string& newText) {
    text = newText;
}