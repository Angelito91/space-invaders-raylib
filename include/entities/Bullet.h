#pragma once
#include "Entity.h"

/**
 * @brief Represents a projectile fired by the player or an alien
 * 
 */
class Bullet: public Entity{ 
public:
    /**
     * @brief Updates the bullet logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the bullet on screen
     */
    virtual void draw() override;
};