#ifndef HAZELENGINE_SPRITERENDERER_H
#define HAZELENGINE_SPRITERENDERER_H

#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"

#include <string>
#include <SDL.h>
#include <GL/glew.h>

enum class TextureFilter{
    Point,
    Bilinear,
    Trilinear,
};

class SpriteRenderer : public Renderer{
public:
    SpriteRenderer(Entity* owner, const std::string& texturePath, TextureFilter = TextureFilter::Point);
    ~SpriteRenderer();

    void Update(float deltaTime) override;
    void Render() override;

    void SetFrame(int x, int y, int width, int height);

    void SetOpacity(float opacity);

private:
    GLuint textureID;
    int textureWidth, textureHeight;
    TextureFilter filterType;

    int frameX, frameY, frameWidth, frameHeight;

    bool LoadTexture(const std::string& texturePath);
    void ApplyFilter();

    float opacity;
};
#endif