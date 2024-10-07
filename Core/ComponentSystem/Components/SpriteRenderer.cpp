#include "SpriteRenderer.h"
#include <iostream>
#include <SDL_image.h>

SpriteRenderer::SpriteRenderer(Entity* owner, std::shared_ptr<Texture> texture, TextureFilter filterType)
        : Renderer(owner), texture(texture), filterType(filterType),
          frameX(0), frameY(0), frameWidth(0), frameHeight(0), opacity(1.0f) {
    ApplyFilter();

    transform = owner->GetComponent<Transform>();
    if (!transform) {
        std::cerr << "No se ha encontrado el componente Transform en el objeto " << std::endl;
    }
}

SpriteRenderer::~SpriteRenderer() {
    // No necesitas eliminar la textura aquí ya que es gestionada por ResourceManager
}

void SpriteRenderer::Update(float deltaTime) {}

void SpriteRenderer::Render(){
    if (!transform || !texture){
        return;
    }

    glm::vec3 pos = transform->position;
    glm::vec3 scale = transform->scale;

    glEnable(GL_TEXTURE_2D);
    texture->Bind();

    glColor4f(1.0f, 1.0f, 1.0f, opacity);

    float width = frameWidth * scale.x;
    float height = frameHeight * scale.y;

    float texX = static_cast<float>(frameX) / texture->width;
    float texY = static_cast<float>(frameY) / texture->height;
    float texWidth = static_cast<float>(frameWidth) / texture->width;
    float texHeight = static_cast<float>(frameHeight) / texture->height;

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

void SpriteRenderer::SetOpacity(float opacity) {
    this->opacity = opacity;
}

void SpriteRenderer::ApplyFilter() {
    if (filterType == TextureFilter::Point){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else if (filterType == TextureFilter::Bilinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else if (filterType == TextureFilter::Trilinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}