#include <raylib.h>
#include <vector>
#include <cstdlib>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Bullet {
    Vector2 pos;
    Vector2 dir;
    float speed;
    bool active;
    bool enemy;
};

struct Enemy {
    Vector2 pos;
    bool alive;
    float shootCooldown;
};

enum class GameState {
    MENU,
    PLAYING,
    GAMEOVER
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "space-invaders");
    SetTargetFPS(60);

    Vector2 playerPos = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT - 50.0f};
    const float playerSpeed = 250.0f;
    const float playerRadius = 20.0f;
    const int maxLives = 3;
    int lives = maxLives;
    int score = 0;
    float playerShootCooldown = 0.0f;

    GameState gameState = GameState::MENU;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    float enemySpeed = 40.0f;
    float enemyDirection = 1.0f;
    float enemyDropY = 20.0f;
    float enemyFireChance = 0.0015f;

    auto spawnEnemies = [&]() {
        enemies.clear();
        const int rows = 5;
        const int cols = 10;
        const float startX = 100.0f;
        const float startY = 80.0f;
        const float spacingX = 58.0f;
        const float spacingY = 48.0f;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                Enemy e;
                e.pos.x = startX + col * spacingX;
                e.pos.y = startY + row * spacingY;
                e.alive = true;
                e.shootCooldown = 0.5f + static_cast<float>(rand()) / RAND_MAX * 1.0f;
                enemies.push_back(e);
            }
        }

        enemySpeed = 40.0f;
        enemyDirection = 1.0f;
        enemyFireChance = 0.0015f;
    };

    spawnEnemies();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (gameState == GameState::MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = GameState::PLAYING;
                lives = maxLives;
                score = 0;
                playerPos = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT - 50.0f};
                bullets.clear();
                spawnEnemies();
            }
        } else if (gameState == GameState::PLAYING) {
            // Player input
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                playerPos.x -= playerSpeed * dt;
            }
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                playerPos.x += playerSpeed * dt;
            }
            playerPos.x = Clamp(playerPos.x, playerRadius, SCREEN_WIDTH - playerRadius);

            if (IsKeyDown(KEY_SPACE) && playerShootCooldown <= 0.0f) {
                Bullet b;
                b.pos = {playerPos.x, playerPos.y - playerRadius - 5};
                b.dir = {0, -1};
                b.speed = 500.0f;
                b.active = true;
                b.enemy = false;
                bullets.push_back(b);
                playerShootCooldown = 0.3f;
            }

            playerShootCooldown -= dt;

            // Enemy movement
            float minX = SCREEN_WIDTH;
            float maxX = 0;
            bool anyAlive = false;

            for (auto &e : enemies) {
                if (!e.alive) continue;
                anyAlive = true;
                minX = fmin(minX, e.pos.x);
                maxX = fmax(maxX, e.pos.x);
            }

            if (!anyAlive) {
                spawnEnemies();
                score += 200;
                enemySpeed += 10.0f;
                enemyFireChance = fmin(0.01f, enemyFireChance + 0.001f);
            }

            if (anyAlive) {
                bool edgeHit = false;
                if (minX <= 30.0f || maxX >= SCREEN_WIDTH - 30.0f) edgeHit = true;

                if (edgeHit) {
                    enemyDirection *= -1.0f;
                    for (auto &e : enemies) {
                        if (e.alive) e.pos.y += enemyDropY;
                    }
                }

                for (auto &e : enemies) {
                    if (!e.alive) continue;
                    e.pos.x += enemySpeed * dt * enemyDirection;

                    // Enemy shoot decision
                    if (static_cast<float>(rand()) / RAND_MAX < enemyFireChance) {
                        Bullet b;
                        b.pos = {e.pos.x, e.pos.y + 12};
                        b.dir = {0, 1};
                        b.speed = 220.0f;
                        b.active = true;
                        b.enemy = true;
                        bullets.push_back(b);
                    }
                }
            }

            // Update bullets
            for (auto &b : bullets) {
                if (!b.active) continue;
                b.pos.x += b.dir.x * b.speed * dt;
                b.pos.y += b.dir.y * b.speed * dt;
                if (b.pos.y < -10 || b.pos.y > SCREEN_HEIGHT + 10) b.active = false;
            }

            // Bullet collisions
            for (auto &b : bullets) {
                if (!b.active) continue;

                if (!b.enemy) {
                    for (auto &e : enemies) {
                        if (!e.alive) continue;
                        if (CheckCollisionCircles(b.pos, 4, e.pos, 10)) {
                            b.active = false;
                            e.alive = false;
                            score += 10;
                            break;
                        }
                    }
                } else {
                    if (CheckCollisionCircles(b.pos, 4, playerPos, playerRadius)) {
                        b.active = false;
                        lives -= 1;
                        if (lives <= 0) gameState = GameState::GAMEOVER;
                    }
                }
            }

            // Enemy reaches player Y => game over
            for (auto &e : enemies) {
                if (e.alive && e.pos.y >= playerPos.y - 40) {
                    gameState = GameState::GAMEOVER;
                }
            }

            // Simple difficulty scaling by remaining enemies
            int remaining = 0;
            for (auto &e : enemies) if (e.alive) remaining++;
            if (remaining > 0) {
                float ratio = 1.0f - (float)remaining / 50.0f;
                enemySpeed = 40.0f + ratio * 120.0f;
            }

        } else if (gameState == GameState::GAMEOVER) {
            if (IsKeyPressed(KEY_R)) {
                gameState = GameState::MENU;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (gameState == GameState::MENU) {
            DrawText("SPACE INVADERS - PRESS ENTER", 170, 260, 20, WHITE);
            DrawText("WASD/ARROWS: MOVIMIENTO  SPACE: DISPARO", 130, 300, 20, LIGHTGRAY);
        } else if (gameState == GameState::PLAYING) {
            // Draw player
            DrawCircle(playerPos.x, playerPos.y, playerRadius, SKYBLUE);

            // Draw enemies
            for (auto &e : enemies) {
                if (!e.alive) continue;
                DrawRectangle(static_cast<int>(e.pos.x)-14, static_cast<int>(e.pos.y)-10, 28, 20, RED);
            }

            // Draw bullets
            for (auto &b : bullets) {
                if (!b.active) continue;
                DrawCircle(b.pos.x, b.pos.y, 4, b.enemy ? ORANGE : GREEN);
            }

            DrawText(FormatText("Score: %04d", score), 10, 10, 20, WHITE);
            DrawText(FormatText("Lives: %d", lives), 10, 34, 20, WHITE);
            DrawText(FormatText("Enemies: %d", std::count_if(enemies.begin(), enemies.end(), [](const Enemy &e){return e.alive;})), 10, 58, 20, WHITE);

            if (IsKeyPressed(KEY_P)) {
                gameState = GameState::MENU;
            }
        } else if (gameState == GameState::GAMEOVER) {
            DrawText("GAME OVER", 330, 250, 30, RAYWHITE);
            DrawText(FormatText("SCORE: %d", score), 340, 290, 24, LIGHTGRAY);
            DrawText("PRESS R TO RESTART", 290, 340, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

