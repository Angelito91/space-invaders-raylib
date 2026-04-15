#pragma once
#include <vector>
#include "Player.h"
#include "Alien.h"
#include "BarrierBlock.h"
#include "Bullet.h"

/**
 * @brief Manages the lifecycle of all game entities
 */
class EntityManager {
private:
    Player player;
    std::vector<Alien> aliens;
    std::vector<BarrierBlock> barrierBlocks;
    std::vector<Bullet> bullets;

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
    Player& getPlayer() { return player; }

    /**
     * @brief Gets a reference to all aliens
     * @return Reference to the aliens vector
     */
    std::vector<Alien>& getAliens() { return aliens; }

    /**
     * @brief Gets a reference to all barrier blocks
     * @return Reference to the barrier blocks vector
     */
    std::vector<BarrierBlock>& getBarrierBlocks() { return barrierBlocks; }

    /**
     * @brief Gets a reference to all bullets
     * @return Reference to the bullets vector
     */
    std::vector<Bullet>& getBullets() { return bullets; }

    /**
     * @brief Initializes all entities with their starting positions
     * @param screenWidth Width of the game screen
     * @param screenHeight Height of the game screen
     */
    void initEntities(int screenWidth, int screenHeight);

    /**
     * @brief Adds a bullet to the game
     * @param b The bullet to add
     */
    void addBullet(Bullet b) { bullets.push_back(b); }

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