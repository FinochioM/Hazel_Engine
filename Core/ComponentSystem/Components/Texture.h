#ifndef HAZELENGINE_TEXTURE_H
#define HAZELENGINE_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <SDL_image.h>
#include <iostream>

class Texture {
public:
    GLuint ID;
    int width, height;

    Texture(const std::string& path){
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface){
            std::cerr << "Failed to load texture: " << path << std::endl;
            return;
        }

        width = surface->w;
        height = surface->h;

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_FreeSurface(surface);
    }


    ~Texture(){
        glDeleteTextures(1, &ID);
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, ID);
    }
};


#endif