#ifndef HAZELENGINE_BUTTON_H
#define HAZELENGINE_BUTTON_H

#include "Widget.h"
#include "TextRenderer.h"
#include "Node.h"

class Button : public Widget, public Node {
public:
    Button(const glm::vec2& position, const glm::vec2& size, const std::string& text, TextRenderer* textRenderer);


    void Render() override;
    void Update(float deltaTime) override;

    void SetText(const std::string& text);

private:
    std::string text;
    TextRenderer* textRenderer;
};

#endif