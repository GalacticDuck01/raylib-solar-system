#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "3d/entity_3d.hpp"

class ResourceManager
{
public:
    static ResourceManager* get() {
        static ResourceManager instance;
        return &instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void loadSound(std::string soundPath);

    void loadTexture(std::string texturePath);

    void tick();

private:
    static ResourceManager* instance;

    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Sound> sounds;

    ResourceManager() = default;
    
    ~ResourceManager();
};