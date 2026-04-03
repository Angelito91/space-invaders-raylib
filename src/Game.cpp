#include "core/Game.h"

#include <raylib.h>

Game::Game()
    : screenWidth(DEFAULT_SCREEN_WIDTH),
      screenHeight(DEFAULT_SCREEN_HEIGHT),
      title("Space Invaders") {}

void Game::init() {
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(DEFAULT_TARGET_FPS);
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw();
        EndDrawing();
    }
}

void Game::update() {
    entityManager.update();
}

void Game::draw() {
    entityManager.draw();
}

void Game::close() {
    CloseWindow();
}

bool Game::checkCollision(const Rectangle& rectA, const Rectangle& rectB) {
    return CheckCollisionRecs(rectA, rectB);
}