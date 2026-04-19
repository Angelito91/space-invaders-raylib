#pragma once
#include <cstdint>

#include "Entity.h"

/**
 * @brief Enum to represent different types of aliens with different point values
 */
enum class AlienType : std::uint8_t { TOP, MIDDLE, BOTTOM };

/**
 * @brief Represents an enemy alien
 */
class Alien : public Entity {
   private:
    // Alien dimensions
    static constexpr float ALIEN_WIDTH  = 40.0F;
    static constexpr float ALIEN_HEIGHT = 30.0F;

    // Animation
    static constexpr float ANIMATION_INTERVAL = 0.5F;

    // Visual components dimensions (relative to position)
    static constexpr int BODY_TOP_WIDTH    = 30;
    static constexpr int BODY_TOP_HEIGHT   = 10;
    static constexpr int BODY_TOP_OFFSET   = 5;
    static constexpr int BODY_MAIN_WIDTH   = 40;
    static constexpr int BODY_MAIN_HEIGHT  = 15;
    static constexpr int BODY_MAIN_OFFSET  = 5;
    static constexpr int LEGS_HEIGHT       = 10;
    static constexpr int LEGS_OFFSET_Y     = 20;
    static constexpr int LEGS_LEFT_OFFSET  = 5;
    static constexpr int LEGS_RIGHT_OFFSET = 25;
    static constexpr int LEGS_WIDTH        = 10;
    static constexpr int ARMS_HEIGHT       = 10;
    static constexpr int ARMS_OFFSET_ALT   = 10;
    static constexpr int ARMS_WIDTH        = 5;
    static constexpr int EYES_Y_OFFSET     = 10;
    static constexpr int EYE_LEFT_X        = 10;
    static constexpr int EYE_RIGHT_X       = 30;

    // Velocity
    static constexpr float INITIAL_VELOCITY = 1.0F;

    AlienType type;
    int       points;
    float     animTimer;
    int       frame;

   public:
    /**
     * @brief Default constructor
     */
    Alien();

    /**
     * @brief Constructor with position and type
     * @param pos Initial position
     * @param t Alien type
     */
    Alien(Vector2 pos, AlienType alienType);

    /**
     * @brief Updates the alien logic every frame
     */
    void update() override;

    /**
     * @brief Draws the alien on screen
     */
    void draw() override;

    /**
     * @brief Gets the alien type
     * @return The alien type
     */
    [[nodiscard]] AlienType getType() const {
        return type;
    }

    /**
     * @brief Gets the points value for this alien
     * @return Points awarded for destroying this alien
     */
    [[nodiscard]] int getPoints() const {
        return points;
    }

    /**
     * @brief Sets the alien type and updates properties accordingly
     * @param t The new alien type
     */
    void setType(AlienType alienType);
};