#pragma once
#include <string>
#include "raylib.h"
#include "AssetManager.h"
#include "EntityManager.h"

/**
 * @brief Main orchestrator of the game loop and systems
 */
class Game {
private:
    static constexpr int DEFAULT_SCREEN_WIDTH = 800;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    static constexpr int DEFAULT_TARGET_FPS = 60;

    int screenWidth;
    int screenHeight;
    std::string title;
    AssetManager assetManager;
    EntityManager entityManager;
    int score;
    int highScore;
    bool gameOver;
    bool paused;
    float alienDirection;
    float alienMoveTimer;
    float alienShootTimer;

    /**
     * @brief Checks collision between two rectangles
     * @param rectA First rectangle
     * @param rectB Second rectangle
     * @return True if they collide
     */
    static bool checkCollision(const Rectangle& rectA, const Rectangle& rectB);

public:
    Game();

    /**
     * @brief Initialize the window and all systems
     */
    void init();

    /**
     * @brief Starts the main game loop
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
     * @brief Shows the game over screen
     */
    void showGameOverScreen();

    /**
     * @brief Closes the window and frees resources
     */
    static void close();

    int getScore() const { return score; }
    int getHighScore() const { return highScore; }
    bool isGameOver() const { return gameOver; }
    void addScore(int points) { score += points; }
    void setGameOver(bool gameOverState) { gameOver = gameOverState; }
    void restart();
};