#pragma once
#include "Entity.h"

/**
 * @brief Represents an enemy alien
 * 
 */
class Alien: public Entity{ 
public:
    /**
     * @brief Updates the alien logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the alien on screen
     */
    virtual void draw() override;
};