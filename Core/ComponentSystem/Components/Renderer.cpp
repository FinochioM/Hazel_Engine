#include "Renderer.h"

#include <GL/glew.h>
#include <iostream>

Renderer::Renderer(Entity* owner)
    : Component(owner), color(glm::vec4(1.0f)) {}


void Renderer::Update(float deltaTime) {}

void Renderer::Render(){
    Transform* transform = static_cast<Transform*>(owner->GetComponent("Transform"));
    if (!transform){
        std::cerr << "No se ha encontrado el componente Transform en el objeto " << std::endl;
        return;
    }

    glm::vec3 pos = transform->position;
    glColor4f(color.r, color.g, color.b, color.a);

    glBegin(GL_QUADS);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x + 50, pos.y);
        glVertex2f(pos.x + 50, pos.y + 50);
        glVertex2f(pos.x, pos.y + 50);
    glEnd();
}