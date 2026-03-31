#pragma once 
#include <map>
#include <string>
#include <vector>
#include "raylib.h"
#include "entities/Player.h"
#include "entities/Alien.h"
#include "entities/BarrierBlock.h"
#include "entities/Bullet.h"

/**
 * @brief Manages the lifecycle of all game entities
 */
class EntityManager{
private:
    Player player;
    std::vector<Alien> aliens;
    std::vector<BarrierBlock> barrierblocks;
    std::vector<Bullet> bullets;

public:
    /**
     * @brief Updates all active entities 
     */
    void Update();

    /**
     * @brief Draws all active entities
     */
    void Draw() ;
};
