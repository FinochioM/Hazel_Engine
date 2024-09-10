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