#pragma once
#include "raylib.h"

class Entity{
protected:
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Color color;
    bool active;
    float width;
    float height;

public:
    Entity();
    Entity(Vector2 pos, Vector2 vel, Color col, float w, float h);
    virtual void Update() = 0;
    virtual void Draw() = 0;

    Rectangle getRect() const {
        return{ position.x, position.y, width, height };
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
