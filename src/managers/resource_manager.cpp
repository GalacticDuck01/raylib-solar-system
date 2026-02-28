#include "resource_manager.hpp"
#include "utils/utils.hpp"

ResourceManager::~ResourceManager() {
    texturesToLoad.clear();
    soundsToLoad.clear();

    for (const Texture& texture : loadedTextures) {
        UnloadTexture(texture);
    }
    loadedTextures.clear();

    loadedSounds.clear();
}

void ResourceManager::tick() {
    unsigned int resourcesToLoad = MAX_RESOURCES_TO_LOAD_PER_TICK;

    for (const std::string& texturePath : texturesToLoad) {
        if (resourcesToLoad <= 0) {
            break;
        }
        if (!FileExists(texturePath.c_str())) {
            error("[ResourceManager::tick] Cannot find texture file: " + texturePath);
        }

        Texture2D texture = LoadTexture(texturePath.c_str());
        loadedTextures.push_back(texture);

        resourcesToLoad--;
    }
    
    for (const std::string& soundPath : soundsToLoad) {
        if (resourcesToLoad <= 0) {
            break;
        }
        if (!FileExists(soundPath.c_str())) {
            error("[ResourceManager::tick] Cannot find sound file: " + soundPath);
        }

        Sound sound = LoadSound(soundPath.c_str());
        loadedSounds.push_back(sound);

        resourcesToLoad--;
    }
}