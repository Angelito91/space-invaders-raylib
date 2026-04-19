#include "entities/Alien.h"

#include "raylib.h"

Alien::Alien() : type(AlienType::BOTTOM), points(10), animTimer(0), frame(0) {
    width    = ALIEN_WIDTH;
    height   = ALIEN_HEIGHT;
    velocity = {INITIAL_VELOCITY, 0};
    color    = RED;
    active   = true;
}

Alien::Alien(Vector2 pos, AlienType alienType)
    : type(alienType), points(10), animTimer(0), frame(0) {
    width    = ALIEN_WIDTH;
    height   = ALIEN_HEIGHT;
    position = pos;
    velocity = {INITIAL_VELOCITY, 0};
    active   = true;
    setType(alienType);
}

void Alien::setType(AlienType alienType) {
    type = alienType;
    switch (type) {
        case AlienType::TOP:
            points = 30;
            color  = MAGENTA;
            break;
        case AlienType::MIDDLE:
            points = 20;
            color  = ORANGE;
            break;
        case AlienType::BOTTOM:
            points = 10;
            color  = RED;
            break;
    }
}

void Alien::update() {
    position.x += velocity.x;
    animTimer += GetFrameTime();
    if (animTimer >= ANIMATION_INTERVAL) {
        frame     = (frame + 1) % 2;
        animTimer = 0;
    }
}

void Alien::draw() {
    Color col = color;
    if (!active) {
        return;
    }

    int posX = static_cast<int>(position.x);
    int posY = static_cast<int>(position.y);

    DrawRectangle(posX + BODY_TOP_OFFSET, posY, BODY_TOP_WIDTH, BODY_TOP_HEIGHT, col);
    DrawRectangle(posX, posY + BODY_MAIN_OFFSET, BODY_MAIN_WIDTH, BODY_MAIN_HEIGHT, col);
    DrawRectangle(posX + BODY_TOP_OFFSET, posY + LEGS_OFFSET_Y, LEGS_WIDTH, LEGS_HEIGHT, col);
    DrawRectangle(posX + LEGS_RIGHT_OFFSET, posY + LEGS_OFFSET_Y, LEGS_WIDTH, LEGS_HEIGHT, col);

    if (frame == 0) {
        DrawRectangle(posX + LEGS_LEFT_OFFSET, posY + BODY_MAIN_OFFSET, ARMS_WIDTH, ARMS_HEIGHT,
                      col);
        DrawRectangle(posX + 35, posY + BODY_MAIN_OFFSET, ARMS_WIDTH, ARMS_HEIGHT, col);
    } else {
        DrawRectangle(posX + LEGS_LEFT_OFFSET, posY + ARMS_OFFSET_ALT, ARMS_WIDTH, ARMS_HEIGHT,
                      col);
        DrawRectangle(posX + 35, posY + ARMS_OFFSET_ALT, ARMS_WIDTH, ARMS_HEIGHT, col);
    }

    DrawPixel(posX + EYE_LEFT_X, posY + EYES_Y_OFFSET, BLACK);
    DrawPixel(posX + EYE_RIGHT_X, posY + EYES_Y_OFFSET, BLACK);
}