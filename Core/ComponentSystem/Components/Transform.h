#ifndef HAZELENGINE_TRANSFORM_H
#define HAZELENGINE_TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>

class Transform : public Component {
public:
    Transform(Entity *owner);

    void Update(float deltaTime) override;

    void Render() override;

    std::string GetTypeName() const override { return "Transform"; }

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};
#endif