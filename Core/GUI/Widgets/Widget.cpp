#include "Widget.h"

void Widget::HandleEvents(const SDL_Event& event){
    if (state == WidgetState::DISABLED || !isVisible) return;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    bool isMouseOver = mouseX >= position.x && mouseX <= position.x + size.x &&
                       mouseY >= position.y && mouseY <= position.y + size.y;

    if (isMouseOver){
        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.button == SDL_BUTTON_LEFT){
                SetState(WidgetState::PRESSED);
                TriggerEvent(WidgetEventType::LeftClick);
            }else if (event.button.button == SDL_BUTTON_RIGHT){
                SetState(WidgetState::PRESSED);
                TriggerEvent(WidgetEventType::RightClick);
            }
        }else if (event.type == SDL_MOUSEMOTION){
            SetState(WidgetState::HOVERED);
            TriggerEvent(WidgetEventType::Hover);
        }
    }else{
        SetState(WidgetState::NORMAL);
        TriggerEvent(WidgetEventType::MouseOut);
    }
}

void Widget::RegisterEvent(WidgetEventType eventType, std::function<void()> callback) {
    eventCallbacks[eventType] = callback;
}

void Widget::TriggerEvent(WidgetEventType eventType) {
    if (eventCallbacks.find(eventType) != eventCallbacks.end()){
        eventCallbacks[eventType]();
    }
}