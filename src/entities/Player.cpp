#include "entities/Player.h"

#include <algorithm>

#include "raylib.h"

Player::Player() {
    width    = PLAYER_WIDTH;
    height   = PLAYER_HEIGHT;
    position = {400.0F - (width / 2.0F), 520.0F};
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

    position.x = std::max<float>(position.x, 0);
    if (position.x + width > 800) {
        position.x = 800 - width;
    }

    lastShot += GetFrameTime();
}

void Player::draw() {
    Color shipColor    = color;
    Color cannonColor  = {150, 150, 150, 255};
    Color cockpitColor = {100, 200, 255, 255};

    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                  static_cast<int>(width), static_cast<int>(height), shipColor);

    DrawRectangle(static_cast<int>(position.x) + CANNON_OFFSET,
                  static_cast<int>(position.y) - CANNON_HEIGHT, CANNON_WIDTH, CANNON_HEIGHT,
                  shipColor);
    DrawRectangle(static_cast<int>(position.x) + static_cast<int>(width) - 20,
                  static_cast<int>(position.y) - CANNON_HEIGHT, CANNON_WIDTH, CANNON_HEIGHT,
                  shipColor);

    DrawRectangle(static_cast<int>(position.x) + CANNON_OFFSET,
                  static_cast<int>(position.y) - (CANNON_HEIGHT + CANNON_INTERNAL_HEIGHT),
                  CANNON_INTERNAL_HEIGHT, CANNON_INTERNAL_HEIGHT, cannonColor);
    DrawRectangle(static_cast<int>(position.x) + static_cast<int>(width) - 15,
                  static_cast<int>(position.y) - (CANNON_HEIGHT + CANNON_INTERNAL_HEIGHT),
                  CANNON_INTERNAL_HEIGHT, CANNON_INTERNAL_HEIGHT, cannonColor);

    DrawRectangle(static_cast<int>(position.x) + static_cast<int>(width / 2) - 8,
                  static_cast<int>(position.y) - COCKPIT_HEIGHT, COCKPIT_WIDTH, COCKPIT_HEIGHT,
                  cockpitColor);

    DrawRectangle(static_cast<int>(position.x) + THRUSTER_OFFSET,
                  static_cast<int>(position.y) + THRUSTER_OFFSET, THRUSTER_WIDTH,
                  static_cast<int>(height) - 5, {50, 150, 50, 255});
    DrawRectangle(static_cast<int>(position.x) + static_cast<int>(width) - 18,
                  static_cast<int>(position.y) + THRUSTER_OFFSET, THRUSTER_WIDTH,
                  static_cast<int>(height) - 5, {50, 150, 50, 255});
}

bool Player::canShoot() const {
    return lastShot >= fireRate;
}

void Player::resetPosition(int screenWidth, int screenHeight) {
    position = {(static_cast<float>(screenWidth) / 2.0F) - (width / 2.0F),
                static_cast<float>(screenHeight) - static_cast<float>(PLAYER_START_Y_OFFSET)};
    lastShot = 0.0F;
}