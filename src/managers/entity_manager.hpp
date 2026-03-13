#pragma once

#include <string>
#include <unordered_map>

#include "3d/entity_3d.hpp"

class EntityManager {
public:
    static EntityManager* get() {
        static EntityManager instance;
        return &instance;
    }

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    void loadEntity(const std::string& name, const Entity3D& entity);

    void render(const Shader& shader);

private:
    std::unordered_map<std::string, const Entity3D*> entities;

    EntityManager() = default;
    ~EntityManager();
};