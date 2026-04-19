#include "entities/Entity.h"

#include "raylib.h"

Entity::Entity() : position{0, 0}, velocity{0, 0}, active(true), width(0), height(0) {
    texture = {0};
    color   = WHITE;
}

Entity::Entity(Vector2 pos, Vector2 vel, Color col, float entityWidth, float entityHeight)
    : position(pos), velocity(vel), active(true), width(entityWidth), height(entityHeight) {
    texture = {0};
    color   = col;
}