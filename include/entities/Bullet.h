#pragma once
#include <cstdint>
#include "Entity.h"

/**
 * @brief Enum to represent different bullet types
 */
enum class BulletType : std::uint8_t { PLAYER, ALIEN };

/**
 * @brief Represents a projectile fired by the player or an alien
 */
class Bullet: public Entity {
private:
    BulletType type;
    float bulletSpeed;

public:
    /**
     * @brief Default constructor
     */
    Bullet();

    /**
     * @brief Constructor with position, velocity and type
     * @param pos Initial position
     * @param vel Initial velocity
     * @param t Bullet type (PLAYER or ALIEN)
     */
    Bullet(Vector2 pos, Vector2 vel, BulletType bulletType);

    /**
     * @brief Updates the bullet logic every frame
     */
    virtual void update() override;
    
    /**
     * @brief Draws the bullet on screen
     */
    virtual void draw() override;

    /**
     * @brief Gets the bullet type
     * @return The bullet type
     */
    BulletType getType() const { return type; }

    /**
     * @brief Checks if this is a player bullet
     * @return True if this bullet was fired by the player
     */
    bool isPlayerBullet() const { return type == BulletType::PLAYER; }
};