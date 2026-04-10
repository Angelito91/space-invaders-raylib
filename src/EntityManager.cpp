#include "core/EntityManager.h"
#include <algorithm>

EntityManager::EntityManager() {
}

void EntityManager::initEntities(int screenWidth, int screenHeight) {
    aliens.clear();
    barrierBlocks.clear();
    bullets.clear();
    
    float startX = 80.0f;
    float startY = 80.0f;
    
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 11; col++) {
            AlienType type;
            if (row == 0) type = AlienType::TOP;
            else if (row < 3) type = AlienType::MIDDLE;
            else type = AlienType::BOTTOM;
            
            Vector2 pos = { startX + col * 60.0f, startY + row * 45.0f };
            aliens.push_back(Alien(pos, type));
        }
    }
    
    float barrierY = 450.0f;
    int barrierPositions[] = { 100, 250, 400, 550 };
    
    for (int b = 0; b < 4; b++) {
        float bx = (float)barrierPositions[b];
        
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 6; col++) {
                bool isHole = false;
                if (row == 3 && (col == 2 || col == 3)) isHole = true;
                
                if (!isHole) {
                    Vector2 pos = { bx + col * 10.0f, barrierY + row * 10.0f };
                    barrierBlocks.push_back(BarrierBlock(pos, GREEN));
                }
            }
        }
    }
    
    player.resetPosition(screenWidth, screenHeight);
}

void EntityManager::Update() {
    player.Update();
    
    for (auto& alien : aliens) {
        alien.Update();
    }
    
    for (auto& bullet : bullets) {
        bullet.Update();
    }
    
    for (auto& block : barrierBlocks) {
        block.Update();
    }
}

void EntityManager::Draw() {
    player.Draw();
    
    for (auto& alien : aliens) {
        alien.Draw();
    }
    
    for (auto& bullet : bullets) {
        bullet.Draw();
    }
    
    for (auto& block : barrierBlocks) {
        block.Draw();
    }
}

void EntityManager::removeInactiveBullets() {
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.isActive(); }),
        bullets.end()
    );
}

void EntityManager::removeInactiveAliens() {
    aliens.erase(
        std::remove_if(aliens.begin(), aliens.end(), [](const Alien& a) { return !a.isActive(); }),
        aliens.end()
    );
}

void EntityManager::removeInactiveBarriers() {
    barrierBlocks.erase(
        std::remove_if(barrierBlocks.begin(), barrierBlocks.end(), [](const BarrierBlock& b) { return !b.isActive(); }),
        barrierBlocks.end()
    );
}

void EntityManager::resetAliens() {
    aliens.clear();
    float startX = 80.0f;
    float startY = 80.0f;
    
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 11; col++) {
            AlienType type;
            if (row == 0) type = AlienType::TOP;
            else if (row < 3) type = AlienType::MIDDLE;
            else type = AlienType::BOTTOM;
            
            Vector2 pos = { startX + col * 60.0f, startY + row * 45.0f };
            aliens.push_back(Alien(pos, type));
        }
    }
}
