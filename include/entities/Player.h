#pragma once
#include "Entity.h"

/**
 * @brief Represents the player-controlled ship
 */
class Player: public Entity {
private:
    int lives;              ///< Remaining lives
    float speed;            ///< Movement speed
    float fireRate;         ///< Time between shots
    float lastShot;         ///< Time since last shot

public:
    /**
     * @brief Default constructor
     */
    Player();

    /**
     * @brief Updates the player logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the ship on screen
     */
    virtual void draw() override;

    /**
     * @brief Gets remaining lives
     * @return Number of lives
     */
    int getLives() const { return lives; }

    /**
     * @brief Sets the number of lives
     * @param l New number of lives
     */
    void setLives(int numLives) { lives = numLives; }

    /**
     * @brief Decrements lives by one
     */
    void decrementLives() { lives--; }

    /**
     * @brief Checks if the player can shoot
     * @return True if enough time has passed to shoot again
     */
    bool canShoot();

    /**
     * @brief Resets player position to center bottom
     * @param screenWidth Width of the screen
     * @param screenHeight Height of the screen
     */
    void resetPosition(int screenWidth, int screenHeight);
};