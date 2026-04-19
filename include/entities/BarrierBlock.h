#pragma once
#include "Entity.h"

/**
 * @brief Represents a single block of a barrier shield
 */
class BarrierBlock : public Entity {
   public:
    /**
     * @brief Default constructor
     */
    BarrierBlock();

    /**
     * @brief Constructor with position and color
     * @param pos Initial position
     * @param col Color of the block
     */
    BarrierBlock(Vector2 pos, Color col);

    /**
     * @brief Updates the block logic every frame
     */
    virtual void update() override;

    /**
     * @brief Draws the block on screen
     */
    virtual void draw() override;
};