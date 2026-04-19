#pragma once
#include <string>

#include "AssetManager.h"
#include "EntityManager.h"
#include "raylib.h"

/**
 * @brief Main orchestrator of the game loop and systems
 */
class Game {
   private:
    // Screen dimensions
    static constexpr int DEFAULT_SCREEN_WIDTH  = 800;
    static constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    static constexpr int DEFAULT_TARGET_FPS    = 60;

    // UI dimensions
    static constexpr int TEXT_SIZE_LARGE  = 60;
    static constexpr int TEXT_SIZE_MEDIUM = 30;
    static constexpr int TEXT_SIZE_SMALL  = 20;
    static constexpr int TEXT_SIZE_TINY   = 15;

    static constexpr int HEADER_HEIGHT = 50;
    static constexpr int FOOTER_HEIGHT = 25;

    // Alien movement
    static constexpr float ALIEN_MOVE_INTERVAL  = 0.5F;
    static constexpr int   ALIEN_MOVE_DISTANCE  = 10;
    static constexpr int   ALIEN_DROP_DISTANCE  = 20;
    static constexpr int   ALIEN_EDGE_MARGIN    = 20;
    static constexpr float ALIEN_SHOOT_INTERVAL = 2.0F;

    // Bullet properties
    static constexpr int BULLET_PLAYER_OFFSET_Y = 12;
    static constexpr int BULLET_OFFSET_X        = 2;

    // Game over screen offsets
    static constexpr int GAME_OVER_TITLE_OFFSET_Y   = 80;
    static constexpr int GAME_OVER_SCORE_OFFSET_Y   = 0;
    static constexpr int GAME_OVER_RESTART_OFFSET_Y = 60;

    // Text positioning
    static constexpr int TEXT_CENTER_OFFSET_X = 120;
    static constexpr int TEXT_LEFT_MARGIN     = 20;
    static constexpr int TEXT_TOP_MARGIN      = 15;

    // UI color values
    static constexpr unsigned char COLOR_BG_R = 20;
    static constexpr unsigned char COLOR_BG_G = 20;
    static constexpr unsigned char COLOR_BG_B = 40;
    static constexpr unsigned char COLOR_BG_A = 255;

    static constexpr unsigned char COLOR_BORDER_R = 50;
    static constexpr unsigned char COLOR_BORDER_G = 50;
    static constexpr unsigned char COLOR_BORDER_B = 80;
    static constexpr unsigned char COLOR_BORDER_A = 255;

    static constexpr unsigned char COLOR_TITLE_R = 100;
    static constexpr unsigned char COLOR_TITLE_G = 255;
    static constexpr unsigned char COLOR_TITLE_B = 100;
    static constexpr unsigned char COLOR_TITLE_A = 255;

    static constexpr unsigned char COLOR_SECONDARY_R = 150;
    static constexpr unsigned char COLOR_SECONDARY_G = 150;
    static constexpr unsigned char COLOR_SECONDARY_B = 150;
    static constexpr unsigned char COLOR_SECONDARY_A = 255;

    static constexpr unsigned char COLOR_SCORE_ALT_R = 200;
    static constexpr unsigned char COLOR_SCORE_ALT_G = 200;
    static constexpr unsigned char COLOR_SCORE_ALT_B = 100;
    static constexpr unsigned char COLOR_SCORE_ALT_A = 255;

    static constexpr unsigned char COLOR_CONTROLS_R = 100;
    static constexpr unsigned char COLOR_CONTROLS_G = 100;
    static constexpr unsigned char COLOR_CONTROLS_B = 100;
    static constexpr unsigned char COLOR_CONTROLS_A = 255;

    int           screenWidth{DEFAULT_SCREEN_WIDTH};
    int           screenHeight{DEFAULT_SCREEN_HEIGHT};
    std::string   title;
    AssetManager  assetManager;
    EntityManager entityManager;
    int           score{0};
    int           highScore{0};
    bool          gameOver{false};
    bool          paused{false};
    float         alienDirection{1.0F};
    float         alienMoveTimer{0.0F};
    float         alienShootTimer{0.0F};

    /**
     * @brief Updates alien movement logic
     */
    void updateAlienMovement();

    /**
     * @brief Updates alien shooting logic
     */
    void updateAlienShooting();

    /**
     * @brief Checks if aliens reached the bottom
     */
    void checkAlienDefeat();

    /**
     * @brief Updates bullet collisions
     */
    void updateBulletCollisions();

    /**
     * @brief Checks collision between two rectangles
     * @param rectA First rectangle
     * @param rectB Second rectangle
     * @return True if they collide
     */
    static bool checkCollision(const Rectangle& rectA, const Rectangle& rectB);

    /**
     * @brief Draws the game header with title and score
     */
    void drawHeader();

    /**
     * @brief Draws the game footer with controls
     */
    void drawFooter() const;

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

    [[nodiscard]] int getScore() const {
        return score;
    }
    [[nodiscard]] int getHighScore() const {
        return highScore;
    }
    [[nodiscard]] bool isGameOver() const {
        return gameOver;
    }
    void addScore(int points) {
        score += points;
    }
    void setGameOver(bool gameOverState) {
        gameOver = gameOverState;
    }
    void restart();
};