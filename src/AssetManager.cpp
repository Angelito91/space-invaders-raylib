#include "AssetManager.h"

Texture2D AssetManager::loadTexture(const std::string& path) {
    auto iterator = textures.find(path);
    if (iterator != textures.end()) {
        return iterator->second;
    }
    Texture2D texture = LoadTexture(path.c_str());
    textures[path] = texture;
    return texture;
}

void AssetManager::unloadAll() {
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    textures.clear();
}