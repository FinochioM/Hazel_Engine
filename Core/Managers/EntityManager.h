#ifndef HAZELENGINE_ENTITYMANAGER_H
#define HAZELENGINE_ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <iostream>
#include "Entity.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Camera2D.h"

class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void AddEntity(const std::shared_ptr<Entity>& entity){
        entities.push_back(entity);
    }

    void Update(){
        for (auto& entity : entities){
            for (auto& component : entity->GetComponents()){
                component->Update();
            }
        }
    }

    void Render(Renderer& renderer, const Camera2D camera){
        for (auto& entity : entities){
            auto transform = entity->GetComponent<Transform>();
            if (transform){
                renderer.Render(*transform, camera);
            }
        }
    }

    void CheckCollisions() {
        for (size_t i = 0; i < entities.size(); i++) {
            for (size_t j = i + 1; j < entities.size(); j++) {
                auto transform1 = entities[i]->GetComponent<Transform>();
                auto collider1 = entities[i]->GetComponent<BoxCollider>();
                auto transform2 = entities[j]->GetComponent<Transform>();
                auto collider2 = entities[j]->GetComponent<BoxCollider>();

                if (transform1 && collider1 && transform2 && collider2) {
                    if (CheckCollision(*transform1, *collider1, *transform2, *collider2)) {
                        std::cout << "Colisión detectada entre entidades " << i << " y " << j << std::endl;
                    }
                }
            }
        }
    }

    bool CheckCollision(const Transform& t1, const BoxCollider& c1, const Transform& t2, const BoxCollider& c2){
        glm::vec2 pos1 = glm::vec2(t1.position.x, t1.position.y);
        glm::vec2 pos2 = glm::vec2(t2.position.x, t2.position.y);

        glm::vec2 halfSize1 = c1.size / 2.0f;
        glm::vec2 halfSize2 = c2.size / 2.0f;

        bool collisionX = pos1.x + halfSize1.x > pos2.x - halfSize2.x &&
                          pos2.x + halfSize2.x > pos1.x - halfSize1.x;
        bool collisionY = pos1.y + halfSize1.y > pos2.y - halfSize2.y &&
                          pos2.y + halfSize2.y > pos1.y - halfSize1.y;

        return collisionX && collisionY;
    }

private:
    std::vector<std::shared_ptr<Entity>> entities;
};

#endif