#ifndef HAZELENGINE_FONTMANAGER_H
#define HAZELENGINE_FONTMANAGER_H

#include <SDL_ttf.h>
#include <GL/glew.h>
#include <string>

class FontManager{
public:
    FontManager();
    ~FontManager();

    bool LoadFont(const std::string& fontPath, int fontSize);
    GLuint RenderTextToTexture(const std::string& text, SDL_Color color, int& width, int& height);

    TTF_Font* GetFont() const {return font;}

private:
    TTF_Font* font;
};

#endif