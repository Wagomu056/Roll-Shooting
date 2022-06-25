//
// Created by 東口拓也 on 2022/06/18.
//

#ifndef BOUND_BALL_BALL_CORE_H
#define BOUND_BALL_BALL_CORE_H

#include "vec2.h"

struct Ball
{
    struct Vec2 pos;
};

struct Ball* createBall(float x, float y, float vx, float vy);
void updateBall(void);

#endif //BOUND_BALL_BALL_CORE_H
