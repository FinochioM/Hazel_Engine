#ifndef HAZELENGINE_WIDGET_H
#define HAZELENGINE_WIDGET_H

#include <glm/glm.hpp>
#include <SDL.h>
#include <map>
#include <functional>
#include <string>

#include "TextRenderer.h"

enum class WidgetState{
    NORMAL,
    HOVERED,
    PRESSED,
    DISABLED
};

enum class WidgetEventType{
    LeftClick,
    RightClick,
    Hover,
    MouseOut,
};

class Widget{
public:
    Widget(const glm::vec2& position, const glm::vec2& size, TextRenderer* textRenderer = nullptr)
        : position(position), size(size), state(WidgetState::NORMAL), isVisible(true), textRenderer(textRenderer) {}

    virtual ~Widget() = default;

    virtual void Render() = 0;
    virtual void Update(float deltaTime) = 0;

    virtual void HandleEvents(const SDL_Event& event);

    void SetVisible(bool visible) {isVisible = visible;}
    bool IsVisible() const {return isVisible;}

    void SetState(WidgetState newState){
        state = newState;
        OnStateChanged();
    }

    WidgetState GetState() const {return state;}

    void RegisterEvent(WidgetEventType eventType, std::function<void()> callback);
    void TriggerEvent(WidgetEventType eventType);

    void RenderTextCentered(const std::string& text, SDL_Color textColor){
        if (textRenderer){
            int textWidth, textHeight;
            textRenderer->GetTextSize(text, textWidth, textHeight);
            glm::vec2 textPos = position + size / 2.0f - glm::vec2(textWidth, textHeight) / 2.0f;
            textRenderer->RenderText(text, textPos, textColor);
        }
    }

protected:
    virtual void OnStateChanged() {}

    TextRenderer* textRenderer;
    glm::vec2 position;
    glm::vec2 size;
    bool isVisible;
    WidgetState state;
    std::map<WidgetEventType, std::function<void()>> eventCallbacks;
};

#endif