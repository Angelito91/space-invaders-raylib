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
class Alien: public Entity {
private:
    AlienType type;
    int points;
    float animTimer;
    int frame;

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
    virtual void update() override;
    
    /**
     * @brief Draws the alien on screen
     */
    virtual void draw() override;

    /**
     * @brief Gets the alien type
     * @return The alien type
     */
    AlienType getType() const { return type; }

    /**
     * @brief Gets the points value for this alien
     * @return Points awarded for destroying this alien
     */
    int getPoints() const { return points; }

    /**
     * @brief Sets the alien type and updates properties accordingly
     * @param t The new alien type
     */
    void setType(AlienType alienType);
};