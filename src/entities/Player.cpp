#include "entities/Player.h"

#include "raylib.h"

Player::Player() : Entity(), lives(3), speed(5.0f), fireRate(0.25f), lastShot(0.0f) {
    width    = 60.0f;
    height   = 20.0f;
    position = {400.0f - width / 2.0f, 520.0f};
    velocity = {0, 0};
    color    = {0, 200, 80, 255};
    active   = true;
}

void Player::update() {
    velocity = {0, 0};

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocity.x = -speed;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocity.x = speed;
    }

    position.x += velocity.x;

    if (position.x < 0) position.x = 0;
    if (position.x + width > 800) position.x = 800 - width;

    lastShot += GetFrameTime();
}

void Player::draw() {
    Color shipColor    = color;
    Color cannonColor  = {150, 150, 150, 255};
    Color cockpitColor = {100, 200, 255, 255};

    DrawRectangle((int)position.x, (int)position.y, (int)width, (int)height, shipColor);

    DrawRectangle((int)position.x + 5, (int)position.y - 8, 15, 8, shipColor);
    DrawRectangle((int)position.x + width - 20, (int)position.y - 8, 15, 8, shipColor);

    DrawRectangle((int)position.x + 5, (int)position.y - 18, 10, 10, cannonColor);
    DrawRectangle((int)position.x + width - 15, (int)position.y - 18, 10, 10, cannonColor);

    DrawRectangle((int)position.x + width / 2 - 8, (int)position.y - 12, 16, 12, cockpitColor);

    DrawRectangle((int)position.x + 10, (int)position.y + 5, 8, (int)height - 5,
                  {50, 150, 50, 255});
    DrawRectangle((int)position.x + width - 18, (int)position.y + 5, 8, (int)height - 5,
                  {50, 150, 50, 255});
}

bool Player::canShoot() {
    return lastShot >= fireRate;
}

void Player::resetPosition(int screenWidth, int screenHeight) {
    position = {(float)screenWidth / 2.0f - width / 2.0f, (float)screenHeight - 80.0f};
    lastShot = 0.0f;
}