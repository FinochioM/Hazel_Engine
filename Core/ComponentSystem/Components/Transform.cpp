#include "Transform.h"

Transform::Transform(Entity* owner)
    : Component(owner), position(0.0f), rotation(0.0f), scale(1.0f) {}

void Transform::Update(float deltaTime) {}

void Transform::Render() {}