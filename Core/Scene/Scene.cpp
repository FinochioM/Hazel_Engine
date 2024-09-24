#include "Scene.h"
#include "Widget.h"

Scene::Scene(const std::string& name) : Node(name) {}

void Scene::Load() { }

void Scene::Unload() { }

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