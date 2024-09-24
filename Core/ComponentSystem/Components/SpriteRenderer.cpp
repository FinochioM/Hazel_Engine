#include "SpriteRenderer.h"
#include <iostream>
#include <SDL_image.h>

SpriteRenderer::SpriteRenderer(Entity* owner, const std::string& texturePath, TextureFilter filterType)
    : Renderer(owner), textureID(0), textureWidth(0), textureHeight(0), filterType(filterType),
      frameX(0), frameY(0), frameWidth(0), frameHeight(0), opacity(1.0f){

    if(!LoadTexture(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteTextures(1, &textureID);
}

void SpriteRenderer::Update(float deltaTime) {}

void SpriteRenderer::Render(){
    Transform* transform = static_cast<Transform*>(owner->GetComponent("Transform"));

    if (!transform){
        std::cerr << "No se ha encontrado el componente Transform en el objeto " << std::endl;
        return;
    }

    glm::vec3 pos = transform->position;
    glm::vec3 scale = transform->scale;

    // Enlazar la textura antes de dibujar
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Asegurarse de que el color sea blanco para que no afecte la textura
    glColor4f(1.0f, 1.0f, 1.0f, opacity);

    float width = frameWidth * scale.x;
    float height = frameHeight * scale.y;

    float texX = (float)frameX / textureWidth;
    float texY = (float)frameY / textureHeight;
    float texWidth = (float)frameWidth / textureWidth;
    float texHeight = (float)frameHeight / textureHeight;

    glBegin(GL_QUADS);
        glTexCoord2f(texX, texY); glVertex2f(pos.x, pos.y);
        glTexCoord2f(texX + texWidth, texY); glVertex2f(pos.x + width, pos.y);
        glTexCoord2f(texX + texWidth, texY + texHeight); glVertex2f(pos.x + width, pos.y + height);
        glTexCoord2f(texX, texY + texHeight); glVertex2f(pos.x, pos.y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void SpriteRenderer::SetFrame(int x, int y, int width, int height) {
    frameX = x;
    frameY = y;
    frameWidth = width;
    frameHeight = height;
}

bool SpriteRenderer::LoadTexture(const std::string &texturePath) {
    SDL_Surface* surface = IMG_Load(texturePath.c_str());

    if (!surface){
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return false;
    }

    textureWidth = surface->w;
    textureHeight = surface->h;


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    ApplyFilter();

    SDL_FreeSurface(surface);
    return true;
}

void SpriteRenderer::ApplyFilter() {
    if (filterType == TextureFilter::Point){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }else if (filterType == TextureFilter::Bilinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else if (filterType == TextureFilter::Trilinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void SpriteRenderer::SetOpacity(float opacity) {
    this->opacity = opacity;
}