#ifndef HAZELENGINE_RENDERER_H
#define HAZELENGINE_RENDERER_H

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

#include <glm/glm.hpp>

class Renderer : public Component {
public:
    Renderer(Entity* owner);

    virtual void Update(float deltaTime) override = 0;
    virtual void Render() override = 0;

    std::string GetTypeName() const override { return "Renderer"; }

    glm::vec4 color;
};
#endif