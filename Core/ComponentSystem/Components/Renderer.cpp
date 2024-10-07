#include "Renderer.h"

#include <GL/glew.h>
#include <iostream>

Renderer::Renderer(Entity* owner)
    : Component(owner), color(glm::vec4(1.0f)) {}