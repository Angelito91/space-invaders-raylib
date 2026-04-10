#include "entities/Bullet.h"

Bullet::Bullet() : Entity(), type(BulletType::PLAYER), bulletSpeed(8.0f) {
    width = 4.0f;
    height = 12.0f;
    color = YELLOW;
    active = true;
}

Bullet::Bullet(Vector2 pos, Vector2 vel, BulletType t) : Entity(), type(t), bulletSpeed(8.0f) {
    width = 4.0f;
    height = 12.0f;
    position = pos;
    velocity = vel;
    active = true;
    
    if (t == BulletType::PLAYER) {
        color = YELLOW;
    } else {
        color = RED;
        bulletSpeed = 4.0f;
    }
}

void Bullet::Update() {
    position.x += velocity.x;
    position.y += velocity.y * bulletSpeed;
    
    if (position.y < 0 || position.y > 650) {
        active = false;
    }
}

void Bullet::Draw() {
    if (!active) return;
    DrawRectangle((int)position.x, (int)position.y, (int)width, (int)height, color);
}
