#pragma once
#include <array>
#include <vector>

#include "Alien.h"
#include "BarrierBlock.h"
#include "Bullet.h"
#include "Player.h"

/**
 * @brief Manages the lifecycle of all game entities
 */
class EntityManager {
   private:
    // Alien grid configuration
    static constexpr int   ALIEN_GRID_ROWS = 5;
    static constexpr int   ALIEN_GRID_COLS = 11;
    static constexpr float ALIEN_START_X   = 80.0F;
    static constexpr float ALIEN_START_Y   = 80.0F;
    static constexpr float ALIEN_SPACING_X = 60.0F;
    static constexpr float ALIEN_SPACING_Y = 45.0F;

    // Barrier configuration
    static constexpr int   BARRIER_COUNT      = 4;
    static constexpr int   BARRIER_POS_1      = 100;
    static constexpr int   BARRIER_POS_2      = 250;
    static constexpr int   BARRIER_POS_3      = 400;
    static constexpr int   BARRIER_POS_4      = 550;
    static constexpr float BARRIER_Y          = 450.0F;
    static constexpr int   BARRIER_ROWS       = 4;
    static constexpr int   BARRIER_COLS       = 6;
    static constexpr float BARRIER_BLOCK_SIZE = 10.0F;

    Player                    player;
    std::vector<Alien>        aliens;
    std::vector<BarrierBlock> barrierBlocks;
    std::vector<Bullet>       bullets;

   public:
    /**
     * @brief Constructor
     */
    EntityManager();

    /**
     * @brief Updates all active entities each frame
     */
    void update();

    /**
     * @brief Draws all active entities on screen
     */
    void draw();

    /**
     * @brief Gets a reference to the player
     * @return Reference to the player entity
     */
    Player& getPlayer() {
        return player;
    }

    /**
     * @brief Gets a reference to all aliens
     * @return Reference to the aliens vector
     */
    std::vector<Alien>& getAliens() {
        return aliens;
    }

    /**
     * @brief Gets a reference to all barrier blocks
     * @return Reference to the barrier blocks vector
     */
    std::vector<BarrierBlock>& getBarrierBlocks() {
        return barrierBlocks;
    }

    /**
     * @brief Gets a reference to all bullets
     * @return Reference to the bullets vector
     */
    std::vector<Bullet>& getBullets() {
        return bullets;
    }

    /**
     * @brief Initializes all entities with their starting positions
     * @param screenWidth Width of the game screen
     * @param screenHeight Height of the game screen
     */
    void initEntities(int screenWidth, int screenHeight);

    /**
     * @brief Adds a bullet to the game
     * @param bullet The bullet to add
     */
    void addBullet(const Bullet& bullet) {
        bullets.push_back(bullet);
    }

    /**
     * @brief Removes all inactive bullets from the game
     */
    void removeInactiveBullets();

    /**
     * @brief Removes all destroyed aliens from the game
     */
    void removeInactiveAliens();

    /**
     * @brief Removes all destroyed barrier blocks from the game
     */
    void removeInactiveBarriers();

    /**
     * @brief Resets all aliens to their starting positions
     */
    void resetAliens();
};