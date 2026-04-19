#pragma once
#include <map>
#include <string>

#include "raylib.h"

/**
 * @brief Manage game assets to avoid duplicate loading
 */
class AssetManager {
   private:
    std::map<std::string, Texture2D> textures;  ///< Loaded textures indexed by name

   public:
    /**
     * @brief Loads a texture from disk or returns if its already loaded
     * @param path Path to the texture file
     * @return The Loaded Texture2D
     */
    Texture2D loadTexture(const std::string& path);

    /**
     * @brief Unloads all loaded textures from memory
     */
    void unloadAll();
};