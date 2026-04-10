#pragma once
#include <vector>
#include "entities/Player.h"
#include "entities/Alien.h"
#include "entities/BarrierBlock.h"
#include "entities/Bullet.h"

class EntityManager {
private:
    Player player;
    std::vector<Alien> aliens;
    std::vector<BarrierBlock> barrierBlocks;
    std::vector<Bullet> bullets;

public:
    EntityManager();

    void Update();
    void Draw();

    Player& getPlayer() { return player; }
    std::vector<Alien>& getAliens() { return aliens; }
    std::vector<BarrierBlock>& getBarrierBlocks() { return barrierBlocks; }
    std::vector<Bullet>& getBullets() { return bullets; }

    void initEntities(int screenWidth, int screenHeight);
    void addBullet(Bullet b) { bullets.push_back(b); }
    void removeInactiveBullets();
    void removeInactiveAliens();
    void removeInactiveBarriers();
    void resetAliens();
};
