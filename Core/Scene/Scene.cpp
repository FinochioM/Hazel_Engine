#include "Scene.h"
#include "Widget.h"

Scene::Scene(const std::string& name) : Node(name) {}

void Scene::Init() {
    std ::cout << "Scene " << name << " initialized" << std::endl;
}

void Scene::Load() {
    std::cout << "Scene " << name << " loaded" << std::endl;
}

void Scene::Unload() {
    std::cout << "Scene " << name << " unloaded" << std::endl;
}

void Scene::Update(float deltaTime) {
    Node::Update(deltaTime);
}

void Scene::Render() {
    Node::Render();
}

void Scene::HandleEvents(const SDL_Event &event) {
    for (Node* child : children){
        Widget* widgetChild = dynamic_cast<Widget*>(child);
        if (widgetChild){
            widgetChild->HandleEvents(event);
        }
    }
}

Entity* Scene::GetEntity(const std::string &entityName) {
    if (entities.find(entityName) != entities.end()){
        return entities[entityName];
    } else {
        return nullptr;
    }
}

void Scene::AddChild(Node* child){
    Node::AddChild(child);

    Entity* entityChild = dynamic_cast<Entity*>(child);
    if (entityChild){
        entities[entityChild->name] = entityChild;
    }
}