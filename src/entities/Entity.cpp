#include "entities/Entity.h"

#include "raylib.h"

Entity::Entity() : position{0, 0}, velocity{0, 0}, active(true), texture{}, color(WHITE) {}

Entity::Entity(Vector2 pos, Vector2 vel, Color col, float entityWidth, float entityHeight)
    : position(pos),
      velocity(vel),
      active(true),
      width(entityWidth),
      height(entityHeight),
      texture{},
      color(col) {}