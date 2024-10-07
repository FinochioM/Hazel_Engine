#ifndef HAZELENGINE_SPRITERENDERER_H
#define HAZELENGINE_SPRITERENDERER_H

#include "Renderer.h"
#include "Entity.h"
#include "Transform.h"
#include "Texture.h"

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
    SpriteRenderer(Entity* owner, std::shared_ptr<Texture> texture, TextureFilter filterType = TextureFilter::Point);
    ~SpriteRenderer();

    void Update(float deltaTime) override;
    void Render() override;

    void SetFrame(int x, int y, int width, int height);
    void SetOpacity(float opacity);

    std::string GetTypeName() const override { return "SpriteRenderer"; }

private:
    std::shared_ptr<Texture> texture;
    TextureFilter filterType;
    Transform* transform;

    int frameX, frameY, frameWidth, frameHeight;
    float opacity;

    void ApplyFilter();
};
#endif