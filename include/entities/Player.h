#pragma once
#include "Entity.h"

class Player : public Entity {
private:
    int lives;
    float speed;
    float fireRate;
    float lastShot;

public:
    Player();
    virtual void Update() override;
    virtual void Draw() override;

    int getLives() const { return lives; }
    void setLives(int l) { lives = l; }
    void decrementLives() { lives--; }
    bool canShoot();
    void resetPosition(int screenWidth, int screenHeight);
};
