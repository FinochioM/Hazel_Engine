#ifndef HAZELENGINE_APPLICATION_H
#define HAZELENGINE_APPLICATION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <iostream>

#include "TextRenderer.h"
#include "FontManager.h"
#include "Global.h"
#include "WidgetManager.h"
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
    SDL_Window* window = nullptr;
    SDL_GLContext glContext;
    FontManager fontManager;
    TextRenderer* textRenderer;
    SceneManager sceneManager;

    bool InitSDL();
    bool InitOpenGL();
    bool InitTTF();
    void GameLoop();
};

#endif