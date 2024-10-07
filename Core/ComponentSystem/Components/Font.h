#ifndef HAZELENGINE_FONT_H
#define HAZELENGINE_FONT_H

#include <string>
#include <SDL_ttf.h>
#include <iostream>

class Font{
public:
    TTF_Font* font;

    Font(const std::string& path, int size){
        font = TTF_OpenFont(path.c_str(), size);
        if (!font){
            std::cerr << "Failed to load font: " << path << std::endl;
        }
    }

    ~Font(){
        if (font){
            TTF_CloseFont(font);
        }
    }

    TTF_Font* GetFont() const {
        return font;
    }
};

#endif