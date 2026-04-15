#pragma once
#include <cstdint>
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
    float width = 0.0F;         ///< Width of the entity
    float height = 0.0F;        ///< Height of the entity
    Color color = WHITE;        ///< Color of the entity

public:
    /**
     * @brief Default constructor
     */
    Entity() = default;

    /**
     * @brief Constructor with initial values
     * @param pos Initial position
     * @param vel Initial velocity
     * @param col Color
     * @param entityWidth Width
     * @param entityHeight Height
     */
    Entity(Vector2 pos, Vector2 vel, Color col, float entityWidth, float entityHeight);

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
     * @brief Returns the collision rectangle derived from position and size
     * @return Rectangle used for collision detection
     */
    Rectangle getRect() const {
        return { position.x, position.y, width, height };
    }

    Vector2 getPosition() const { return position; }
    void setPosition(Vector2 pos) { position = pos; }
    Vector2 getVelocity() const { return velocity; }
    void setVelocity(Vector2 vel) { velocity = vel; }
    bool isActive() const { return active; }
    void setActive(bool act) { active = act; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    Color getColor() const { return color; }

    virtual ~Entity() = default;
};