#pragma once
#include "Entity.h"

enum class AlienType { TOP, MIDDLE, BOTTOM };

class Alien : public Entity {
private:
    AlienType type;
    int points;
    float animTimer;
    int frame;

public:
    Alien();
    Alien(Vector2 pos, AlienType t);
    virtual void Update() override;
    virtual void Draw() override;

    AlienType getType() const { return type; }
    int getPoints() const { return points; }
    void setType(AlienType t);
};
