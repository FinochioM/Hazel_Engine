#include "Node.h"
#include <algorithm>


Node::Node(const std::string& name)
    : name(name), pos(0.0f, 0.0f) {}


void Node::Update(float deltaTime){
    for (Node* child : children){
        child->Update(deltaTime);
    }
}

void Node::Render(){
    for (Node* child : children){
        child->Render();
    }
}

void Node::AddChild(Node* child){
    children.push_back(child);
}

void Node::RemoveChild(Node* child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

Node* Node::GetChild(const std::string& name){
    for (Node* child : children){
        if (child->name == name){
            return child;
        }
    }

    return nullptr;
}

void Node::SetPosition(const glm::vec3 &position) {
    pos = position;
}

glm::vec2 Node::GetPosition() const{
    return pos;
}