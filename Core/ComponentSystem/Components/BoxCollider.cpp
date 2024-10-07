#include "BoxCollider.h"
#include <iostream>


BoxCollider::BoxCollider(Entity *owner, const glm::vec2 &size)
    : Component(owner), size(size) {}

void BoxCollider::Update(float deltaTime) {}

void BoxCollider::Render(){
    Transform* transform = owner->GetComponent<Transform>();

    if (!transform){
        std::cerr << "No se ha encontrado el componente Transform en el objeto " << std::endl;
        return;
    }

    glm::vec3 pos = transform->position;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x + size.x, pos.y);
        glVertex2f(pos.x + size.x, pos.y + size.y);
        glVertex2f(pos.x, pos.y + size.y);
    glEnd();
}

glm::vec2 BoxCollider::GetPosition() const {
    Transform* transform = owner->GetComponent<Transform>();
    if (transform){
        return glm::vec2(transform->position);
    }
    return glm::vec2(0.0f);
}

glm::vec2 BoxCollider::GetSize() const {
    return size;
}