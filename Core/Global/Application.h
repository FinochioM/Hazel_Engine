#ifndef HAZELENGINE_APPLICATION_H
#define HAZELENGINE_APPLICATION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <iostream>

#include "TextRenderer.h"
#include "Global.h"
#include "WidgetManager.h"
#include "WindowManager.h"
#include "Button.h"
#include "SceneManager.h"



class Application{
public:
    Application();
    ~Application();

    bool Init();
    void Run();
    void Shutdown();

private:
    void GameLoop();

    std::unique_ptr<WindowManager> windowManager;
    std::unique_ptr<SceneManager> sceneManager;
    TextRenderer* textRenderer;
    bool isRunning;
};

#endif