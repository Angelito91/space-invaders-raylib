#pragma once
#include "Entity.h"

/**
 * @brief Represents the player-controlled ship
 * 
 */
class Player: public Entity{
private:
    int lives; ///< Remaining lives

public:
    /**
     * @brief Updates the player logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the ship on screen
     */
    virtual void draw() override;
};