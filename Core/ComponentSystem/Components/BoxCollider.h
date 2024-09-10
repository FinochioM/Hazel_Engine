#ifndef HAZELENGINE_BOXCOLLIDER_H
#define HAZELENGINE_BOXCOLLIDER_H

#include "Component.h"
#include "Transform.h"
#include "Entity.h"

#include <glm/glm.hpp>
#include <GL/glew.h>

class BoxCollider : public Component{
public:
    BoxCollider(Entity* owner, const glm::vec2& size);

    void Update(float deltaTime) override;
    void Render() override;

    std::string GetTypeName() const override { return "BoxCollider"; }

    glm::vec2 GetPosition() const;
    glm::vec2 GetSize() const;

private:
    glm::vec2 size;
};
#endif