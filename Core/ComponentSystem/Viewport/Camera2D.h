#ifndef HAZELENGINE_CAMERA2D_H
#define HAZELENGINE_CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D{
public:
    glm::vec2 position;
    float zoom;
    float rotation;
    float viewportWidth, viewportHeight;


    Camera2D(float viewportWidth, float viewportHeight)
        : position(0.0f, 0.0f), zoom(1.0f), rotation(0.0f),
        viewportWidth(viewportWidth), viewportHeight(viewportHeight) {}

    glm::mat4 GetViewMatrix() const{
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
        view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0f,0.0f,1.0f));
        view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
        return view;
    }

    glm::mat4 GetProjectionMatrix() const{
        float halfWidth = viewportWidth * 0.5f;
        float halfHeight = viewportHeight * 0.5f;

        return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
    }

    glm::mat4 GetViewProjectionMatrix() const{
        return GetProjectionMatrix() * GetViewMatrix();
    }

    void Move(const glm::vec2& delta){
        position += delta;
    }

    void Zoom(float factor){
        zoom *= factor;
    }

    void Rotate(float angle){
        rotation += angle;
    }
};

#endif