#ifndef HAZELENGINE_SCENEMANAGER_H
#define HAZELENGINE_SCENEMANAGER_H

#include "Scene.h"
#include <map>
#include <string>

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void AddScene(Scene* scene);
    void RemoveScene(const std::string& sceneName);

    void SetCurrentScene(const std::string& sceneName);
    Scene* GetCurrentScene() const;

    void Update(float deltaTime);
    void Render();

private:
    std::map<std::string, Scene*> scenes;  // Almacena todas las escenas
    Scene* currentScene;  // La escena actual activa
};
#endif