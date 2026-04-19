#include "core/Game.h"

#include <vector>

#include "entities/Alien.h"
#include "entities/Bullet.h"
#include "raylib.h"

Game::Game()
    : screenWidth(DEFAULT_SCREEN_WIDTH),
      screenHeight(DEFAULT_SCREEN_HEIGHT),
      title("Space Invaders"),
      score(0),
      highScore(0),
      gameOver(false),
      paused(false),
      alienDirection(1.0F),
      alienMoveTimer(0.0F),
      alienShootTimer(0.0F) {}

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

        DrawRectangle(0, 0, screenWidth, screenHeight,
                      {COLOR_BG_R, COLOR_BG_G, COLOR_BG_B, COLOR_BG_A});

        DrawText("GAME OVER", (screenWidth / 2) - (MeasureText("GAME OVER", TEXT_SIZE_LARGE) / 2),
                 (screenHeight / 2) - 80, TEXT_SIZE_LARGE, RED);

        const char* scoreText = TextFormat("Puntuacion Final: %d", score);
        DrawText(scoreText, (screenWidth / 2) - (MeasureText(scoreText, TEXT_SIZE_MEDIUM) / 2),
                 screenHeight / 2, TEXT_SIZE_MEDIUM, WHITE);

        const char* controlsText = "Presiona ENTER para reiniciar";
        DrawText(controlsText, (screenWidth / 2) - (MeasureText(controlsText, TEXT_SIZE_SMALL) / 2),
                 (screenHeight / 2) + 60, TEXT_SIZE_SMALL,
                 {COLOR_SECONDARY_R, COLOR_SECONDARY_G, COLOR_SECONDARY_B, COLOR_SECONDARY_A});

        EndDrawing();
    }
}

void Game::updateAlienMovement() {
    alienMoveTimer += GetFrameTime();
    if (alienMoveTimer < ALIEN_MOVE_INTERVAL) {
        return;
    }

    alienMoveTimer = 0.0F;

    bool needDrop = false;
    for (auto& alien : entityManager.getAliens()) {
        if (!alien.isActive()) {
            continue;
        }

        const float rightEdge = alien.getPosition().x + alien.getWidth();
        const float leftEdge  = alien.getPosition().x;

        if ((alienDirection > 0 && rightEdge >= (screenWidth - ALIEN_EDGE_MARGIN)) ||
            (alienDirection < 0 && leftEdge <= ALIEN_EDGE_MARGIN)) {
            needDrop = true;
            break;
        }
    }

    for (auto& alien : entityManager.getAliens()) {
        if (!alien.isActive()) {
            continue;
        }

        Vector2 currentPos = alien.getPosition();
        if (needDrop) {
            alien.setPosition({currentPos.x, currentPos.y + ALIEN_DROP_DISTANCE});
        } else {
            const float newX = currentPos.x + (ALIEN_MOVE_DISTANCE * alienDirection);
            alien.setPosition({newX, currentPos.y});
        }
    }

    if (needDrop) {
        alienDirection *= -1.0F;
    }
}

void Game::updateAlienShooting() {
    alienShootTimer += GetFrameTime();
    if (alienShootTimer < ALIEN_SHOOT_INTERVAL) {
        return;
    }

    alienShootTimer = 0.0F;

    std::vector<Alien> activeAliens;
    for (auto& alien : entityManager.getAliens()) {
        if (alien.isActive()) {
            activeAliens.push_back(alien);
        }
    }

    if (activeAliens.empty()) {
        return;
    }

    int          randIdx    = GetRandomValue(0, static_cast<int>(activeAliens.size()) - 1);
    const Alien& shooter    = activeAliens[randIdx];
    Vector2      shooterPos = shooter.getPosition();
    Vector2      bulletPos  = {shooterPos.x + (shooter.getWidth() / 2.0F) - BULLET_OFFSET_X,
                               shooterPos.y + shooter.getHeight()};

    Bullet bullet(bulletPos, {0.0F, 1.0F}, BulletType::ALIEN);
    entityManager.addBullet(bullet);
}

void Game::checkAlienDefeat() {
    for (const auto& alien : entityManager.getAliens()) {
        if (!alien.isActive()) {
            continue;
        }

        const float alienBottom = alien.getPosition().y + alien.getHeight();
        const float playerTop   = entityManager.getPlayer().getPosition().y;

        if (alienBottom >= playerTop) {
            gameOver = true;
            return;
        }
    }
}

void Game::updateBulletCollisions() {
    for (auto& bullet : entityManager.getBullets()) {
        if (!bullet.isActive()) {
            continue;
        }

        if (bullet.isPlayerBullet()) {
            for (auto& alien : entityManager.getAliens()) {
                if (!alien.isActive()) {
                    continue;
                }
                if (checkCollision(bullet.getRect(), alien.getRect())) {
                    bullet.setActive(false);
                    alien.setActive(false);
                    addScore(alien.getPoints());
                    break;
                }
            }

            for (auto& block : entityManager.getBarrierBlocks()) {
                if (!block.isActive()) {
                    continue;
                }
                if (checkCollision(bullet.getRect(), block.getRect())) {
                    bullet.setActive(false);
                    block.setActive(false);
                    break;
                }
            }
        } else {
            const Rectangle playerRect = entityManager.getPlayer().getRect();
            if (checkCollision(bullet.getRect(), playerRect)) {
                bullet.setActive(false);
                entityManager.getPlayer().decrementLives();
                if (entityManager.getPlayer().getLives() <= 0) {
                    gameOver = true;
                }
            }

            for (auto& block : entityManager.getBarrierBlocks()) {
                if (!block.isActive()) {
                    continue;
                }
                if (checkCollision(bullet.getRect(), block.getRect())) {
                    bullet.setActive(false);
                    block.setActive(false);
                    break;
                }
            }
        }
    }
}

void Game::update() {
    entityManager.update();

    if (IsKeyPressed(KEY_SPACE) && entityManager.getPlayer().canShoot()) {
        Vector2 playerPos   = entityManager.getPlayer().getPosition();
        float   playerWidth = entityManager.getPlayer().getWidth();
        Vector2 bulletPos   = {playerPos.x + (playerWidth / 2.0F) - BULLET_OFFSET_X,
                               playerPos.y - BULLET_PLAYER_OFFSET_Y};

        Bullet bullet(bulletPos, {0.0F, -1.0F}, BulletType::PLAYER);
        entityManager.addBullet(bullet);
    }

    updateAlienMovement();
    updateAlienShooting();
    checkAlienDefeat();
    updateBulletCollisions();

    entityManager.removeInactiveBullets();
    entityManager.removeInactiveAliens();
    entityManager.removeInactiveBarriers();

    if (entityManager.getAliens().empty()) {
        entityManager.resetAliens();
        alienDirection = 1.0F;
    }
}

void Game::drawHeader() {
    DrawRectangle(0, 0, screenWidth, HEADER_HEIGHT,
                  {COLOR_BORDER_R, COLOR_BORDER_G, COLOR_BORDER_B, COLOR_BORDER_A});

    DrawRectangleLines(0, 0, screenWidth, screenHeight,
                       {COLOR_BORDER_R, COLOR_BORDER_G, COLOR_BORDER_B, COLOR_BORDER_A});

    DrawLine(0, HEADER_HEIGHT, screenWidth, HEADER_HEIGHT,
             {COLOR_BORDER_R, COLOR_BORDER_G, COLOR_BORDER_B, COLOR_BORDER_A});

    const char* titleText  = "SPACE INVADERS";
    const int   titleWidth = MeasureText(titleText, TEXT_SIZE_SMALL);
    DrawText(titleText, (screenWidth / 2) - (titleWidth / 2), 15, TEXT_SIZE_SMALL,
             {COLOR_TITLE_R, COLOR_TITLE_G, COLOR_TITLE_B, COLOR_TITLE_A});

    const char* scoreText = TextFormat("PUNTOS: %d", score);
    DrawText(scoreText, 20, 15, TEXT_SIZE_SMALL, YELLOW);

    if (score > highScore) {
        highScore = score;
    }

    const char* highScoreText  = TextFormat("MEJOR: %d", highScore);
    const int   highScoreWidth = MeasureText(highScoreText, TEXT_SIZE_SMALL);
    DrawText(highScoreText, (screenWidth / 2) - (highScoreWidth / 2), 15, TEXT_SIZE_SMALL,
             {COLOR_SCORE_ALT_R, COLOR_SCORE_ALT_G, COLOR_SCORE_ALT_B, COLOR_SCORE_ALT_A});

    const char* livesText = TextFormat("VIDAS: %d", entityManager.getPlayer().getLives());
    DrawText(livesText, screenWidth - 120, 15, TEXT_SIZE_SMALL, RED);
}

void Game::drawFooter() const {
    const char* controlsText  = "CONTROLES: <- -> Mover  |  ESPACIO: Disparar";
    const int   controlsWidth = MeasureText(controlsText, TEXT_SIZE_TINY);
    DrawText(controlsText, (screenWidth / 2) - (controlsWidth / 2), screenHeight - FOOTER_HEIGHT,
             TEXT_SIZE_TINY,
             {COLOR_CONTROLS_R, COLOR_CONTROLS_G, COLOR_CONTROLS_B, COLOR_CONTROLS_A});
}

void Game::draw() {
    drawHeader();
    entityManager.draw();
    drawFooter();
}

void Game::close() {
    CloseWindow();
}

bool Game::checkCollision(const Rectangle& rectA, const Rectangle& rectB) {
    return CheckCollisionRecs(rectA, rectB);
}

void Game::restart() {
    score           = 0;
    gameOver        = false;
    paused          = false;
    alienDirection  = 1.0F;
    alienMoveTimer  = 0.0F;
    alienShootTimer = 0.0F;
    entityManager.initEntities(screenWidth, screenHeight);
}