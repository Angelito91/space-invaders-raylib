#pragma once
#include <string>
#include "raylib.h"
#include "AssetManager.h"
#include "EntityManager.h"

/**
 * @brief Main orchestator of the game loop and systems
 */
class Game {
private:
    int ScreenWidth,
        ScreenHeight;
    std::string title;
    AssetManager assetManager;
    EntityManager entityManager;

    /**
     * @brief Checks collision between two rectangles
     * @param a First rectangle
     * @param b Second rectangle
     * @return True if they collide
     */
    bool CheckCollision(const Rectangle &a, const Rectangle &b);

public:
    /**
     * @brief Initialize the window and all systems
     */
    void Init();

    /**
     * @brief Stars the main game loop
     */
    void Run();

    /**
     * @brief Updates game logic every frame
     */
    void Update();

    /**
     * @brief Draws everything on screen
     */
    void Draw();

    /**
     * @brief Closes the window and frees resources
     */
    void Close();
};