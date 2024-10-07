#ifndef HAZELENGINE_SCENEMANAGER_H
#define HAZELENGINE_SCENEMANAGER_H

#include "Scene.h"
#include "Entity.h"
#include <map>
#include <string>

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void AddScene(std::shared_ptr<Scene> scene);
    void RemoveScene(const std::string& sceneName);

    void SetCurrentScene(const std::string& sceneName);
    std::shared_ptr<Scene> GetCurrentScene() const;

    void Update(float deltaTime);
    void Render();

private:
    std::map<std::string, std::shared_ptr<Scene>> scenes;  // Almacena todas las escenas
    std::shared_ptr<Scene> currentScene;  // La escena actual activa
};
#endif