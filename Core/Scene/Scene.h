#ifndef HAZELENGINE_SCENE_H
#define HAZELENGINE_SCENE_H

#include "Node.h"
#include "Entity.h"

#include <SDL.h>
#include <map>

class Scene : public Node {
public:
    Scene(const std::string& name);
    ~Scene() = default;


    void Load();
    void Unload();

    void Update(float deltaTime) override;
    void Render() override;

    void HandleEvents(const SDL_Event& event);


    Entity* GetEntity(const std::string& entityName);
    void AddChild(Node* child) override;

private:
    std::map<std::string, Entity*> entities;
};
#endif