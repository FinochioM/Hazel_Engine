#ifndef HAZELENGINE_NODE_H
#define HAZELENGINE_NODE_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Node {
public:
    Node(const std::string& name);
    virtual ~Node() = default;

    virtual void Init();
    virtual void Update(float deltaTime);
    virtual void Render();

    // Ciclo de vida

    virtual void AddChild(Node* child);
    void RemoveChild(Node* child);
    Node* GetChild(const std::string& name);

    void SetPosition(const glm::vec3& position);
    glm::vec2 GetPosition() const;

    std::string name;
protected:
    glm::vec2 pos;
    std::vector<Node*> children;
};
#endif