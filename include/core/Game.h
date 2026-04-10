#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include "AssetManager.h"
#include "EntityManager.h"

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

    static bool checkCollision(const Rectangle& rectA, const Rectangle& rectB);

public:
    Game();
    void init();
    void run();
    void update();
    void draw();
    void showGameOverScreen();
    static void close();

    int getScore() const { return score; }
    int getHighScore() const { return highScore; }
    bool isGameOver() const { return gameOver; }
    void addScore(int points) { score += points; }
    void setGameOver(bool go) { gameOver = go; }
    void restart();
};
