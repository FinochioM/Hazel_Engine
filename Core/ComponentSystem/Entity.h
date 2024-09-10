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

    void AddComponent(Component *component);

    void RemoveComponent(Component *component);

    Component *GetComponent(const std::string &componentName);

    void Update(float deltaTime) override;

    void Render() override;

protected:
    std::vector<std::unique_ptr<Component>> components;
};
#endif