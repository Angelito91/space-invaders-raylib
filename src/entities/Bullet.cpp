#include "entities/Bullet.h"

#include "raylib.h"

Bullet::Bullet() : type(BulletType::PLAYER), bulletSpeed(PLAYER_BULLET_SPEED) {
    width  = BULLET_WIDTH;
    height = BULLET_HEIGHT;
    color  = YELLOW;
    active = true;
}

Bullet::Bullet(Vector2 pos, Vector2 vel, BulletType bulletType)
    : type(bulletType), bulletSpeed(PLAYER_BULLET_SPEED) {
    width    = BULLET_WIDTH;
    height   = BULLET_HEIGHT;
    position = pos;
    velocity = vel;
    active   = true;

    if (bulletType == BulletType::PLAYER) {
        color = YELLOW;
    } else {
        color       = RED;
        bulletSpeed = ALIEN_BULLET_SPEED;
    }
}

void Bullet::update() {
    position.x += velocity.x;
    position.y += velocity.y * bulletSpeed;

    if (position.y < 0 || position.y > BULLET_SCREEN_LIMIT) {
        active = false;
    }
}

void Bullet::draw() {
    if (!active) {
        return;
    }
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                  static_cast<int>(width), static_cast<int>(height), color);
}