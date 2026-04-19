#include "entities/BarrierBlock.h"

#include "raylib.h"

BarrierBlock::BarrierBlock() {
    width  = 10.0F;
    height = 10.0F;
    color  = GREEN;
    active = true;
}

BarrierBlock::BarrierBlock(Vector2 pos, Color col) {
    width    = 10.0F;
    height   = 10.0F;
    position = pos;
    color    = col;
    active   = true;
}

void BarrierBlock::update() {}

void BarrierBlock::draw() {
    if (!active) {
        return;
    }
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                  static_cast<int>(width), static_cast<int>(height), color);
}