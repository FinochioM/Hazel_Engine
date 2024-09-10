#ifndef HAZELENGINE_WIDGETMANAGETR_H
#define HAZELENGINE_WIDGETMANAGETR_H

#include <vector>
#include "Widget.h"

class WidgetManager {
public:
    WidgetManager() = default;
    ~WidgetManager();

    void AddWidget(Widget* widget);
    void RemoveWidget(Widget* widget);

    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);
    void Render();

private:
    std::vector<Widget*> widgets;
};

#endif