#include "entities/Entity.h"

Entity::Entity() : position{0, 0}, velocity{0, 0}, active(true), width(0), height(0) {
    texture = { 0 };
    color = WHITE;
}

Entity::Entity(Vector2 pos, Vector2 vel, Color col, float w, float h)
    : position(pos), velocity(vel), active(true), width(w), height(h) {
    texture = { 0 };
    color = col;
}
