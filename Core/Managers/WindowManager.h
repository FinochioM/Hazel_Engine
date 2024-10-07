#ifndef HAZELENGINE_WINDOWMANAGER_H
#define HAZELENGINE_WINDOWMANAGER_H

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    bool Init(const std::string& title, int width, int height);
    void ShutDown();

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }

private:
    SDL_Window* window;
    SDL_GLContext glContext;
};
#endif