#pragma once
#include "Entity.h"

/**
 * @brief Represents the player-controlled ship
 */
class Player : public Entity {
   private:
    // Player dimensions
    static constexpr float PLAYER_WIDTH         = 60.0F;
    static constexpr float PLAYER_HEIGHT        = 20.0F;
    static constexpr float PLAYER_SPEED         = 5.0F;
    static constexpr float PLAYER_FIRE_RATE     = 0.25F;
    static constexpr float PLAYER_DEFAULT_LIVES = 3.0F;

    // Player positioning
    static constexpr int PLAYER_START_Y_OFFSET = 80;

    // Visual components dimensions
    static constexpr int CANNON_WIDTH           = 15;
    static constexpr int CANNON_HEIGHT          = 8;
    static constexpr int CANNON_OFFSET          = 5;
    static constexpr int CANNON_INTERNAL_HEIGHT = 10;
    static constexpr int COCKPIT_WIDTH          = 16;
    static constexpr int COCKPIT_HEIGHT         = 12;
    static constexpr int THRUSTERS_HEIGHT       = 8;
    static constexpr int THRUSTER_WIDTH         = 8;
    static constexpr int THRUSTER_OFFSET        = 10;

    int   lives{3};                    ///< Remaining lives
    float speed{PLAYER_SPEED};         ///< Movement speed
    float fireRate{PLAYER_FIRE_RATE};  ///< Time between shots
    float lastShot{0.0F};              ///< Time since last shot

   public:
    /**
     * @brief Default constructor
     */
    Player();

    /**
     * @brief Updates the player logic every frame
     */
    void update() override;

    /**
     * @brief Draws the ship on screen
     */
    void draw() override;

    /**
     * @brief Gets remaining lives
     * @return Number of lives
     */
    [[nodiscard]] int getLives() const {
        return lives;
    }

    /**
     * @brief Sets the number of lives
     * @param l New number of lives
     */
    void setLives(int numLives) {
        lives = numLives;
    }

    /**
     * @brief Decrements lives by one
     */
    void decrementLives() {
        lives--;
    }

    /**
     * @brief Checks if the player can shoot
     * @return True if enough time has passed to shoot again
     */
    bool canShoot() const;

    /**
     * @brief Resets player position to center bottom
     * @param screenWidth Width of the screen
     * @param screenHeight Height of the screen
     */
    void resetPosition(int screenWidth, int screenHeight);
};