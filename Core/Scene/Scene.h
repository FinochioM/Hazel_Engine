#ifndef HAZELENGINE_SCENE_H
#define HAZELENGINE_SCENE_H

#include "Node.h"
#include <SDL.h>

class Scene : public Node {
public:
    Scene(const std::string& name);
    ~Scene() = default;


    void Load();
    void Unload();

    void Update(float deltaTime) override;
    void Render() override;

    void HandleEvents(const SDL_Event& event);
};
#endif