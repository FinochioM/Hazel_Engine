#include "FontManager.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>

FontManager::FontManager() : font(nullptr) {}

FontManager::~FontManager() {
    if (font){
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

bool FontManager::LoadFont(const std::string &fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font){
        std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

GLuint FontManager::RenderTextToTexture(const std::string &text, SDL_Color color, int &width, int &height) {
    SDL_Surface* originalSurface;
    SDL_Surface* textSurface;
    GLuint textureID;

    originalSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!originalSurface) {
        std::cerr << "Error al renderizar el texto: " << TTF_GetError() << std::endl;
        return 0;
    }

    textSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_ABGR8888, 0);
    if (!textSurface) {
        std::cerr << "Error al convertir la superficie: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(originalSurface);
        return 0;
    }

    width = textSurface->w;
    height = textSurface->h;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    SDL_FreeSurface(originalSurface);  // Liberar la superficie original
    SDL_FreeSurface(textSurface);      // Liberar la superficie convertida

    return textureID;
}