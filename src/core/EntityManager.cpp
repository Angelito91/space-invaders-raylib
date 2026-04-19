#include "core/EntityManager.h"

#include <algorithm>
#include <array>

#include "entities/Alien.h"
#include "entities/BarrierBlock.h"
#include "entities/Bullet.h"
#include "entities/Player.h"

EntityManager::EntityManager() = default;

void EntityManager::initEntities(int screenWidth, int screenHeight) {
    aliens.clear();
    barrierBlocks.clear();
    bullets.clear();

    // Initialize aliens in grid
    for (int row = 0; row < ALIEN_GRID_ROWS; row++) {
        for (int col = 0; col < ALIEN_GRID_COLS; col++) {
            AlienType alienType = AlienType::BOTTOM;
            if (row == 0) {
                alienType = AlienType::TOP;
            } else if (row < 3) {
                alienType = AlienType::MIDDLE;
            }

            Vector2 pos = {ALIEN_START_X + (static_cast<float>(col) * ALIEN_SPACING_X),
                           ALIEN_START_Y + (static_cast<float>(row) * ALIEN_SPACING_Y)};
            aliens.emplace_back(pos, alienType);
        }
    }

    // Barrier positions
    constexpr std::array<int, BARRIER_COUNT> barrierPositions = {100, 250, 400, 550};

    // Initialize barriers
    for (int barrierPosition : barrierPositions) {
        auto barrierX = static_cast<float>(barrierPosition);

        for (int row = 0; row < BARRIER_ROWS; row++) {
            for (int col = 0; col < BARRIER_COLS; col++) {
                bool isHole = false;
                if (row == 3 && (col == 2 || col == 3)) {
                    isHole = true;
                }

                if (!isHole) {
                    Vector2 pos = {barrierX + (static_cast<float>(col) * BARRIER_BLOCK_SIZE),
                                   BARRIER_Y + (static_cast<float>(row) * BARRIER_BLOCK_SIZE)};
                    barrierBlocks.emplace_back(pos, GREEN);
                }
            }
        }
    }

    player.resetPosition(screenWidth, screenHeight);
}

void EntityManager::update() {
    player.update();

    for (auto& alien : aliens) {
        alien.update();
    }

    for (auto& bullet : bullets) {
        bullet.update();
    }

    for (auto& block : barrierBlocks) {
        block.update();
    }
}

void EntityManager::draw() {
    player.draw();

    for (auto& alien : aliens) {
        alien.draw();
    }

    for (auto& bullet : bullets) {
        bullet.draw();
    }

    for (auto& block : barrierBlocks) {
        block.draw();
    }
}

void EntityManager::removeInactiveBullets() {
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& bullet) { return !bullet.isActive(); }),
                  bullets.end());
}

void EntityManager::removeInactiveAliens() {
    aliens.erase(std::remove_if(aliens.begin(), aliens.end(),
                                [](const Alien& alien) { return !alien.isActive(); }),
                 aliens.end());
}

void EntityManager::removeInactiveBarriers() {
    barrierBlocks.erase(std::remove_if(barrierBlocks.begin(), barrierBlocks.end(),
                                       [](const BarrierBlock& block) { return !block.isActive(); }),
                        barrierBlocks.end());
}

void EntityManager::resetAliens() {
    aliens.clear();

    // Reinitialize aliens in grid
    for (int row = 0; row < ALIEN_GRID_ROWS; row++) {
        for (int col = 0; col < ALIEN_GRID_COLS; col++) {
            AlienType alienType = AlienType::BOTTOM;
            if (row == 0) {
                alienType = AlienType::TOP;
            } else if (row < 3) {
                alienType = AlienType::MIDDLE;
            }

            Vector2 pos = {ALIEN_START_X + (static_cast<float>(col) * ALIEN_SPACING_X),
                           ALIEN_START_Y + (static_cast<float>(row) * ALIEN_SPACING_Y)};
            aliens.emplace_back(pos, alienType);
        }
    }
}