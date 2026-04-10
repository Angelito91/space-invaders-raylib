#pragma once
#include "Entity.h"

class BarrierBlock : public Entity {
public:
    BarrierBlock();
    BarrierBlock(Vector2 pos, Color col);
    virtual void Update() override;
    virtual void Draw() override;
};
