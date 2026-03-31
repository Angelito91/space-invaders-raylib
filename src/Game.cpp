#include "core/Game.h"
#include <raylib.h>

Game::Game() {
    ScreenWidth = 800;
    ScreenHeight = 600;
    title = "Space Invaders";
}

void Game::Init(){
    InitWindow(ScreenWidth, ScreenHeight, title.c_str());
    SetTargetFPS(60);
}

void Game::Run(){
    while (!WindowShouldClose()){
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}

void Game::Update(){
    // Update logic
}

void Game::Draw(){
    // Draw logic
}

void Game::Close(){
    CloseWindow();
}

bool Game::CheckCollision(const Rectangle &a, const Rectangle &b) {
    return CheckCollisionRecs(a, b);
}