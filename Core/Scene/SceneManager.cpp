#include "SceneManager.h"

SceneManager::SceneManager() : currentScene(nullptr) {}

SceneManager::~SceneManager() {
    for (auto &scenePair: scenes) {
        delete scenePair.second;
    }
    scenes.clear();
}

void SceneManager::AddScene(Scene* scene){
    scenes[scene->name] = scene;
}

void SceneManager::RemoveScene(const std::string& sceneName){
    scenes.erase(sceneName);
}

void SceneManager::SetCurrentScene(const std::string& sceneName){
    currentScene = scenes[sceneName];
}

Scene* SceneManager::GetCurrentScene() const{
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