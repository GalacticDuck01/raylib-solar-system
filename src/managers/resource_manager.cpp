#include "resource_manager.hpp"
#include "utils/utils.hpp"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::~ResourceManager() {
    for (const auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
    for (const auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    textures.clear();
}

void ResourceManager::loadSound(std::string soundPath) {
    if (!FileExists(soundPath.c_str())) {
        error("[ResourceManager::loadSound] Cannot find sound file: '" + soundPath + "'");
    }

    Sound sound = LoadSound(soundPath.c_str());
    sounds[soundPath] = sound;
}

void ResourceManager::loadTexture(std::string texturePath) {
    if (!FileExists(texturePath.c_str())) {
        error("[ResourceManager::loadTexture] Cannot find texture file: '" + texturePath + "'");
    }

    Texture2D texture = LoadTexture(texturePath.c_str());
    textures[texturePath] = texture;
}

void ResourceManager::tick() {
}