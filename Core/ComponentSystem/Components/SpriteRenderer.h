#ifndef HAZELENGINE_SPRITERENDERER_H
#define HAZELENGINE_SPRITERENDERER_H

#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"

#include <string>
#include <SDL.h>
#include <GL/glew.h>

class SpriteRenderer {
public:
    SpriteRenderer(Entity* owner, const std::string& texturePath);
    ~SpriteRenderer();

    void Update(float deltaTime) override;
    void Render() override;

private:
    GLuint textureID;
    int textureWidth, textureHeight;

    bool LoadTexture(const std::string& texturePath);
};
#endif