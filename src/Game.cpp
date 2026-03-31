#include "Game.h"
#include "raylib"

void Game::Init(){
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTragetFPS(60);
}

void Game::Run(){
    Init();
    while (!WindowShouldCose()){
        Update();
        BegingDrawing();
        ClearBacground(BLACK);
        Draw()
        EndDrawing();
    }
    Close();
}

void Game::Update(){
}

void Game::Draw(){
}

void Game::Close(){
    CloseWindow();
}

bool Game::CheckCollision(const Rectangle &a, const Rectangle &b){
    return CheckCollisionRecs(a, b);
}