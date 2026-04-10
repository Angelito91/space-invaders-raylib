#include "entities/Alien.h"

Alien::Alien() : Entity(), type(AlienType::BOTTOM), points(10), animTimer(0), frame(0) {
    width = 40.0f;
    height = 30.0f;
    velocity = { 1.0f, 0 };
    color = RED;
    active = true;
}

Alien::Alien(Vector2 pos, AlienType t) : Entity(), type(t), points(10), animTimer(0), frame(0) {
    width = 40.0f;
    height = 30.0f;
    position = pos;
    velocity = { 1.0f, 0 };
    active = true;
    setType(t);
}

void Alien::setType(AlienType t) {
    type = t;
    switch (type) {
        case AlienType::TOP: points = 30; color = MAGENTA; break;
        case AlienType::MIDDLE: points = 20; color = ORANGE; break;
        case AlienType::BOTTOM: points = 10; color = RED; break;
    }
}

void Alien::Update() {
    position.x += velocity.x;
    animTimer += GetFrameTime();
    if (animTimer >= 0.5f) {
        frame = (frame + 1) % 2;
        animTimer = 0;
    }
}

void Alien::Draw() {
    Color col = color;
    if (!active) return;
    
    int x = (int)position.x;
    int y = (int)position.y;
    
    DrawRectangle(x + 5, y, 30, 10, col);
    DrawRectangle(x, y + 5, 40, 15, col);
    DrawRectangle(x + 5, y + 20, 10, 10, col);
    DrawRectangle(x + 25, y + 20, 10, 10, col);
    
    if (frame == 0) {
        DrawRectangle(x, y + 5, 5, 10, col);
        DrawRectangle(x + 35, y + 5, 5, 10, col);
    } else {
        DrawRectangle(x, y + 10, 5, 10, col);
        DrawRectangle(x + 35, y + 10, 5, 10, col);
    }
    
    DrawPixel(x + 10, y + 10, BLACK);
    DrawPixel(x + 30, y + 10, BLACK);
}
