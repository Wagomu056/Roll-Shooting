//
// Created by 東口拓也 on 2022/06/22.
//

#include "include/player.h"

#include "vec2.h"
#include "math_util.h"
#include "../bullet/include/bullet_manager.h"
#include "log.h"
#include "defines.h"

const struct Vec2 DRAW_DIR_BASE = {0.0f, -100.0f};
const struct Vec2 BALL_SPEED = {0.0f, -5.0f};
const float ROTATE_RATIO = 1.0f / 4.0f; // １週するのに5回転必要

static struct Vec2 plPos = {200, 210};
static float currentRad = 0.0f;

static const int FIRE_INTERVAL_MIN = 5;
static const int FIRE_INTERVAL_MAX = 60;
static int fireInterval = 0;
static int currentFireInterval = FIRE_INTERVAL_MAX;

void updatePlayer( PlaydateAPI *pd )
{
    PlaydateAPI* _pd = pd;

    float crankChange = pd->system->getCrankChange();
    float changeRad = degreeToRadian(crankChange);
    currentRad += changeRad * ROTATE_RATIO;

    struct Vec2 drawDir = {0};
    rotateVec2(&DRAW_DIR_BASE, currentRad, &drawDir);
    pd->graphics->drawLine(
            plPos.x, plPos.y,
            plPos.x + drawDir.x, plPos.y + drawDir.y,
            3, kColorBlack);

    fireInterval--;
    if (fireInterval <= 0)
    {
        struct Vec2 vel = {0};
        rotateVec2(&BALL_SPEED, currentRad, &vel);
        addBullet(plPos.x, plPos.y, vel.x, vel.y);

        fireInterval = currentFireInterval;
    }

    PDButtons current, pushed;
    pd->system->getButtonState(&current, &pushed, NULL);
    if ( pushed & kButtonA )
    {
        currentFireInterval -= 5;
        if (currentFireInterval < FIRE_INTERVAL_MIN)
            currentFireInterval = FIRE_INTERVAL_MIN;
        if (currentFireInterval > FIRE_INTERVAL_MAX)
            currentFireInterval = FIRE_INTERVAL_MAX;
        LOG("interval:%d", currentFireInterval);
    }


    if ( current & kButtonLeft )
    {
        plPos.x -= 5;
    }
    else if ( current & kButtonRight )
    {
        plPos.x += 5;
    }
    plPos.x = clamp(plPos.x, 0, DISPLAY_WIDTH );
}
