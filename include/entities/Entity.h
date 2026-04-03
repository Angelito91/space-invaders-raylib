#pragma once
#include "raylib.h"

/**
 * @brief Abstract base class for all game entities 
 */
class Entity {
protected:
    Vector2 position = {};      ///< Position in the world
    Vector2 velocity = {};      ///< Movement speed and direction
    Texture2D texture = {};     ///< Entity sprite
    bool active = false;        ///< Whether the entity is active

public:
    /**
     * @brief Default constructor
     */
    Entity() = default;

    /**
     * @brief Copy constructor
     */
    Entity(const Entity&) = default;

    /**
     * @brief Copy assignment operator
     */
    Entity& operator=(const Entity&) = default;

    /**
     * @brief Move constructor
     */
    Entity(Entity&&) = default;

    /**
     * @brief Move assignment operator
     */
    Entity& operator=(Entity&&) = default;

    /**
     * @brief Updates the entity logic every frame 
     */
    virtual void update() = 0;

    /**
     * @brief Draws the entity on screen
     */
    virtual void draw() = 0;

    /**
     * @brief Returns the collision rectangle derived from position and texture size 
     * @return Rectangle used for collision detection
     */
    Rectangle getRect() {
        return {position.x, position.y, (float)texture.width, (float)texture.height};
    }

    virtual ~Entity() = default;
};