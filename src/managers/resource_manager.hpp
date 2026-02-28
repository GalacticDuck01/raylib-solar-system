#pragma once

#include <string>
#include <vector>

#include "raylib.h"

class ResourceManager
{
public:
    ResourceManager() = default;
    
    ~ResourceManager();

    ResourceManager(const ResourceManager&) = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;

    void loadTexture(std::string texturePath) { texturesToLoad.push_back(texturePath); };

    void loadSound(std::string soundPath) { soundsToLoad.push_back(soundPath); };

    void tick();

private:
    const unsigned int MAX_RESOURCES_TO_LOAD_PER_TICK = 1;

    std::vector<std::string> texturesToLoad;
    std::vector<std::string> soundsToLoad;

    std::vector<Texture2D> loadedTextures;
    std::vector<Sound> loadedSounds;
};