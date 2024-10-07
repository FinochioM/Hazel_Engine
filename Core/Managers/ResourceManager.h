#ifndef HAZELENGINE_RESOURCEMANAGER_H
#define HAZELENGINE_RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <iostream>


class Texture;
class Font;
class Animation;
class Shader;

class ResourceManager {
public:
    static ResourceManager& GetInstance(){
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    template <typename T, typename... Args>
    std::shared_ptr<T> Load(const std::string& name, Args&&... args);

    template <typename T>
    std::shared_ptr<T> Get(const std::string& name);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<void>>> resources;
};

template <typename T, typename... Args>
std::shared_ptr<T> ResourceManager::Load(const std::string& name, Args&&... args){
    std::type_index typeIndex(typeid(T));
    auto& typeMap = resources[typeIndex];

    // Verificar si el recurso ya está cargado
    auto it = typeMap.find(name);
    if (it != typeMap.end()){
        return std::static_pointer_cast<T>(it->second);
    }

    // Cargar el recurso con múltiples argumentos
    std::shared_ptr<T> resource = std::make_shared<T>(std::forward<Args>(args)...);
    if (!resource){
        std::cerr << "Failed to load resource: " << name << std::endl;
        return nullptr;
    }

    // Almacenar en el mapa
    typeMap[name] = resource;
    return resource;
}

template <typename T>
std::shared_ptr<T> ResourceManager::Get(const std::string& name){
    std::type_index typeIndex(typeid(T));
    auto& typeMap = resources[typeIndex];
    auto it = typeMap.find(name);
    if (it != typeMap.end()){
        return std::static_pointer_cast<T>(it->second);
    }

    std::cerr << "Resource not found: " << name << std::endl;
    return nullptr;
}

#endif