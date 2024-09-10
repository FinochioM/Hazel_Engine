#include "WidgetManager.h"
#include <iostream>

WidgetManager::~WidgetManager() {
    for (auto widget : widgets) {
        delete widget;
    }

    widgets.clear();
}

void WidgetManager::AddWidget(Widget *widget) {
    widgets.push_back(widget);
}

void WidgetManager::RemoveWidget(Widget *widget) {
    widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
}

void WidgetManager::HandleEvents(const SDL_Event& event){
    for (Widget* widget : widgets){
        widget->HandleEvents(event);
    }
}

void WidgetManager::Update(float deltaTime){
    for (Widget* widget : widgets){
        widget->Update(deltaTime);
    }
}

void WidgetManager::Render(){
    for (Widget* widget : widgets){
        widget->Render();
    }
}