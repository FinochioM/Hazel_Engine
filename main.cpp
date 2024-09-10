#include <iostream>
#include <SDL.h>

#include "Global/Application.h"

int main(int argc, char* args[])
{
    Application app;

    if (app.Init()) {
        app.Run();
    }

    return 0;
}