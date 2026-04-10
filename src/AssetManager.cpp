#include "core/AssetManager.h"

Texture2D AssetManager::LoadTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }
    
    Texture2D texture = LoadTexture(path.c_str());
    if (texture.id != 0) {
        textures[path] = texture;
    }
    return texture;
}

void AssetManager::UnloadAll() {
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    textures.clear();
}
