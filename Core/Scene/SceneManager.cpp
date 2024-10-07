#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager() : currentScene(nullptr) {}

SceneManager::~SceneManager() {
    // Liberar todas las escenas
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene){
    scenes[scene->name] = scene;
}

void SceneManager::RemoveScene(const std::string& sceneName){
    scenes.erase(sceneName);
}

void SceneManager::SetCurrentScene(const std::string& sceneName){
    if (currentScene){
        currentScene->Unload();
    }

    auto it = scenes.find(sceneName);
    if (it != scenes.end()) {
        currentScene = it->second;
        currentScene->Init();
        currentScene->Load();
    } else {
        std::cerr << "Scene not found: " << sceneName << std::endl;
    }
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() const{
    return currentScene;
}

void SceneManager::Update(float deltaTime){
    if (currentScene){
        currentScene->Update(deltaTime);
    }
}

void SceneManager::Render(){
    if (currentScene){
        currentScene->Render();
    }
}