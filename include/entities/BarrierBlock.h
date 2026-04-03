#pragma once
#include "Entity.h"

/**
 * @brief Represents a single block of a barrier shield
 * 
 */
class BarrierBlock: public Entity{
public:
    /**
     * @brief Updates the block logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the block on screen
     */
    virtual void draw() override;
};