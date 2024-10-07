#ifndef HAZELENGINE_ENTITY_H
#define HAZELENGINE_ENTITY_H

#include "Node.h"
#include <vector>
#include <string>
#include <memory>

class Component;

class Entity : public Node {
public:
    Entity(const std::string& name);
    virtual ~Entity();

    void AddComponent(std::unique_ptr<Component> component);
    void RemoveComponent(Component *component);

    Component* GetComponentByName(const std::string& componentName) const;

    template <typename T>
    T* GetComponent() const {
        for (const auto& component : components) {
            if (auto casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    void Update(float deltaTime) override;
    void Render() override;

protected:
    std::vector<std::unique_ptr<Component>> components;
};
#endif