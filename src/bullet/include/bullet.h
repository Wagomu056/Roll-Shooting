//
// Created by 東口拓也 on 2022/06/25.
//

#ifndef ROLL_SHOOTING_BULLET_H
#define ROLL_SHOOTING_BULLET_H

#include <vec2.h>
#include "pd_api.h"

struct Bullet
{
    struct Vec2 pos;
    struct Vec2 vel;
    LCDSprite* sprite;
};

#endif //ROLL_SHOOTING_BULLET_H
