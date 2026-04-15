#include "Game.h"
#include "Alien.h"
#include "raylib.h"
#include <vector>

Game::Game() : screenWidth(DEFAULT_SCREEN_WIDTH), screenHeight(DEFAULT_SCREEN_HEIGHT),
               title("Space Invaders"), score(0), highScore(0), gameOver(false), paused(false),
               alienDirection(1.0f), alienMoveTimer(0.0f), alienShootTimer(0.0f) {
}

void Game::init() {
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(DEFAULT_TARGET_FPS);
    entityManager.initEntities(screenWidth, screenHeight);
}

void Game::run() {
    while (!WindowShouldClose() && !gameOver) {
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }
    
    if (gameOver) {
        showGameOverScreen();
    }
}

void Game::showGameOverScreen() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            restart();
            run();
            return;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawRectangle(0, 0, screenWidth, screenHeight, { 20, 20, 40, 255 });
        
        DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 60)/2, screenHeight/2 - 80, 60, RED);
        
        DrawText(TextFormat("Puntuacion Final: %d", score), screenWidth/2 - MeasureText(TextFormat("Puntuacion Final: %d", score), 30)/2, screenHeight/2, 30, WHITE);
        
        DrawText("Presiona ENTER para reiniciar", screenWidth/2 - MeasureText("Presiona ENTER para reiniciar", 20)/2, screenHeight/2 + 60, 20, { 150, 150, 150, 255 });
        
        EndDrawing();
    }
}

void Game::update() {
    entityManager.update();
    
    if (IsKeyPressed(KEY_SPACE) && entityManager.getPlayer().canShoot()) {
        Vector2 pos = entityManager.getPlayer().getPosition();
        float pw = entityManager.getPlayer().getWidth();
        Bullet bullet({ pos.x + pw / 2 - 2, pos.y - 12 }, { 0, -1 }, BulletType::PLAYER);
        entityManager.addBullet(bullet);
    }
    
    alienMoveTimer += GetFrameTime();
    if (alienMoveTimer >= 0.5f) {
        alienMoveTimer = 0.0f;
        
        bool needDrop = false;
        for (auto& alien : entityManager.getAliens()) {
            if (!alien.isActive()) continue;
            if ((alienDirection > 0 && alien.getPosition().x + alien.getWidth() >= screenWidth - 20) ||
                (alienDirection < 0 && alien.getPosition().x <= 20)) {
                needDrop = true;
                break;
            }
        }
        
        for (auto& alien : entityManager.getAliens()) {
            if (!alien.isActive()) continue;
            if (needDrop) {
                alien.setPosition({ alien.getPosition().x, alien.getPosition().y + 20 });
            } else {
                alien.setPosition({ alien.getPosition().x + 10 * alienDirection, alien.getPosition().y });
            }
        }
        
        if (needDrop) {
            alienDirection *= -1;
        }
    }
    
    for (auto& alien : entityManager.getAliens()) {
        if (!alien.isActive()) continue;
        if (alien.getPosition().y + alien.getHeight() >= entityManager.getPlayer().getPosition().y) {
            gameOver = true;
            return;
        }
    }
    
    alienShootTimer += GetFrameTime();
    if (alienShootTimer >= 2.0f) {
        alienShootTimer = 0.0f;
        
        std::vector<Alien> activeAliens;
        for (auto& alien : entityManager.getAliens()) {
            if (alien.isActive()) activeAliens.push_back(alien);
        }
        
        if (!activeAliens.empty()) {
            int randIdx = GetRandomValue(0, (int)activeAliens.size() - 1);
            Alien shooter = activeAliens[randIdx];
            Vector2 pos = shooter.getPosition();
            Bullet bullet({ pos.x + shooter.getWidth() / 2 - 2, pos.y + shooter.getHeight() }, { 0, 1 }, BulletType::ALIEN);
            entityManager.addBullet(bullet);
        }
    }
    
    for (auto& bullet : entityManager.getBullets()) {
        if (!bullet.isActive()) continue;
        
        if (bullet.isPlayerBullet()) {
            for (auto& alien : entityManager.getAliens()) {
                if (!alien.isActive()) continue;
                if (checkCollision(bullet.getRect(), alien.getRect())) {
                    bullet.setActive(false);
                    alien.setActive(false);
                    addScore(alien.getPoints());
                    break;
                }
            }
            
            for (auto& block : entityManager.getBarrierBlocks()) {
                if (!block.isActive()) continue;
                if (checkCollision(bullet.getRect(), block.getRect())) {
                    bullet.setActive(false);
                    block.setActive(false);
                    break;
                }
            }
        } else {
            if (checkCollision(bullet.getRect(), entityManager.getPlayer().getRect())) {
                bullet.setActive(false);
                entityManager.getPlayer().decrementLives();
                if (entityManager.getPlayer().getLives() <= 0) {
                    gameOver = true;
                }
            }
            
            for (auto& block : entityManager.getBarrierBlocks()) {
                if (!block.isActive()) continue;
                if (checkCollision(bullet.getRect(), block.getRect())) {
                    bullet.setActive(false);
                    block.setActive(false);
                    break;
                }
            }
        }
    }
    
    entityManager.removeInactiveBullets();
    entityManager.removeInactiveAliens();
    entityManager.removeInactiveBarriers();
    
    if (entityManager.getAliens().empty()) {
        entityManager.resetAliens();
        alienDirection = 1.0f;
    }
}

void Game::draw() {
    DrawRectangle(0, 0, screenWidth, 50, { 30, 30, 50, 255 });
    
    DrawRectangleLines(0, 0, screenWidth, screenHeight, { 50, 50, 80, 255 });
    
    DrawLine(0, 50, screenWidth, 50, { 50, 50, 80, 255 });
    
    DrawText("SPACE INVADERS", screenWidth/2 - MeasureText("SPACE INVADERS", 20)/2, 15, 20, { 100, 255, 100, 255 });
    
    DrawText(TextFormat("PUNTOS: %d", score), 20, 15, 20, YELLOW);
    
    if (score > highScore) highScore = score;
    DrawText(TextFormat("MEJOR: %d", highScore), screenWidth/2 - MeasureText(TextFormat("MEJOR: %d", highScore), 20)/2, 15, 20, { 200, 200, 100, 255 });
    
    DrawText(TextFormat("VIDAS: %d", entityManager.getPlayer().getLives()), screenWidth - 120, 15, 20, RED);
    
    entityManager.draw();
    
    DrawText("CONTROLES: <- -> Mover  |  ESPACIO: Disparar", screenWidth/2 - MeasureText("CONTROLES: <- -> Mover  |  ESPACIO: Disparar", 15)/2, screenHeight - 25, 15, { 100, 100, 100, 255 });
}

void Game::close() {
    CloseWindow();
}

bool Game::checkCollision(const Rectangle& rectA, const Rectangle& rectB) {
    return CheckCollisionRecs(rectA, rectB);
}

void Game::restart() {
    score = 0;
    gameOver = false;
    paused = false;
    alienDirection = 1.0f;
    alienMoveTimer = 0.0f;
    alienShootTimer = 0.0f;
    entityManager.initEntities(screenWidth, screenHeight);
}