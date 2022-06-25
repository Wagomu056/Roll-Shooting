//
// Created by 東口拓也 on 2022/06/18.
//
#include <stdio.h>
#include "include/ball_core.h"
#include "include/vec2.h"
#include "include/defines.h"

static struct Ball _ball_array[BALL_MAX];
static int _ball_num = 0;

static struct Vec2 _velocities[BALL_MAX];

struct Ball* createBall(float x, float y, float vx, float vy)
{
    if (_ball_num >= BALL_MAX) return NULL;

    struct Ball* b = &(_ball_array[_ball_num]);
    b->pos.x = x;
    b->pos.y = y;

    _velocities[_ball_num].x = vx;
    _velocities[_ball_num].y = vy;

    _ball_num++;
    return b;
}

static const int DISPLAY_WIDTH = 400;
static const int DISPLAY_HEIGHT = 240;

// @todo 画面外に行ったら消える

static const int BALL_WIDTH = 4;//20;
static const int BALL_HEIGHT = 4;//20;
void updateBall(void)
{
    int i;
    for (int i = 0; i < _ball_num; i++)
    {
        _ball_array[i].pos.x += _velocities[i].x;
        _ball_array[i].pos.y += _velocities[i].y;

        if (_ball_array[i].pos.y >= (DISPLAY_HEIGHT - BALL_HEIGHT) ||
            _ball_array[i].pos.y <= 0)
        {
           _velocities[i].y *= -1;
        }

        if (_ball_array[i].pos.x >= (DISPLAY_WIDTH - BALL_WIDTH) ||
            _ball_array[i].pos.x <= 0)
        {
            _velocities[i].x *= -1;
        }
    }
}

