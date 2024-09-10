#include <algorithm>
#include "Entity.h"
#include "Component.h"

Entity::Entity(const std::string& name) : Node(name) {}

Entity::~Entity() { }

void Entity::AddComponent(Component *component) {
    components.emplace_back(component);
}

void Entity::RemoveComponent(Component *component) {
    components.erase(std::remove_if(components.begin(), components.end(),
                                    [component](const std::unique_ptr<Component>& c) {return c.get() == component;}),
                     components.end());
}

Component* Entity::GetComponent(const std::string& typeName){
    for (const auto& component : components){
        if (component->GetTypeName() == typeName){
            return component.get();
        }
    }
    return nullptr;
}

void Entity::Update(float deltaTime){
    Node::Update(deltaTime);
    for  (const auto& component : components){
        component->Update(deltaTime);
    }
}

void Entity::Render(){
    Node::Render();
    for (const auto& component : components){
        component->Render();
    }
}