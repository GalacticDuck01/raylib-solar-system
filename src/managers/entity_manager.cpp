#include "entity_manager.hpp"

#include "utils/utils.hpp"

EntityManager::~EntityManager() {
    entities.clear();
}

void EntityManager::loadEntity(const std::string& name, const Entity3D& node) {
    if (entities.find(name) != entities.end()) {
        warning("[EntityManager::loadEntity] Unnecessary load. Entity '" + name + "' already loaded.");
        return;
    }

    entities[name] = &node;
}

void EntityManager::render(const Shader& shader) {
    for (const auto& pair : entities) {
        pair.second->render(shader);
    }
}