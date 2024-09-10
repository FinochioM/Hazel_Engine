#ifndef HAZELENGINE_COMPONENT_H
#define HAZELENGINE_COMPONENT_H

#include <string>

class Entity;

class Component{
public:
    Component(Entity* owner);
    virtual ~Component() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual std::string GetTypeName() const = 0;

protected:
    Entity* owner;
};

#endif