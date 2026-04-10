#pragma once
#include "Entity.h"

enum class BulletType { PLAYER, ALIEN };

class Bullet : public Entity {
private:
    BulletType type;
    float bulletSpeed;

public:
    Bullet();
    Bullet(Vector2 pos, Vector2 vel, BulletType t);
    virtual void Update() override;
    virtual void Draw() override;

    BulletType getType() const { return type; }
    bool isPlayerBullet() const { return type == BulletType::PLAYER; }
};
