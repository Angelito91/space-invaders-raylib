#include "BarrierBlock.h"

BarrierBlock::BarrierBlock() : Entity() {
    width = 10.0f;
    height = 10.0f;
    color = GREEN;
    active = true;
}

BarrierBlock::BarrierBlock(Vector2 pos, Color col) : Entity() {
    width = 10.0f;
    height = 10.0f;
    position = pos;
    color = col;
    active = true;
}

void BarrierBlock::update() {
}

void BarrierBlock::draw() {
    if (!active) return;
    DrawRectangle((int)position.x, (int)position.y, (int)width, (int)height, color);
}