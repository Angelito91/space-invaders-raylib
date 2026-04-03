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
    static constexpr int DEFAULT_SCREEN_WIDTH = 800;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    static constexpr int DEFAULT_TARGET_FPS = 60;

    int screenWidth,
        screenHeight;
    std::string title;
    AssetManager assetManager;
    EntityManager entityManager;

    /**
     * @brief Checks collision between two rectangles
     * @param a First rectangle
     * @param b Second rectangle
     * @return True if they collide
     */
    static bool checkCollision(const Rectangle &rectA, const Rectangle &rectB);

public:
    Game();

    /**
     * @brief Initialize the window and all systems
     */
    void init();

    /**
     * @brief Stars the main game loop
     */
    void run();

    /**
     * @brief Updates game logic every frame
     */
    void update();

    /**
     * @brief Draws everything on screen
     */
    void draw();

    /**
     * @brief Closes the window and frees resources
     */
    static void close();
};
