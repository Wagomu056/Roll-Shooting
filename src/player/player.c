//
// Created by 東口拓也 on 2022/06/22.
//

#include "../gamepd/include/player_pd.h"

#include "../gamepd/include/ball_pd.h"
#include "vec2.h"
#include "math_util.h"
#include "../bullet/include/bullet_manager.h"

const struct Vec2 DRAW_DIR_BASE = {0.0f, -100.0f};
const struct Vec2 BALL_SPEED = {0.0f, -5.0f};
const float ROTATE_RATIO = 1.0f / 4.0f; // １週するのに5回転必要

static struct Vec2 plPos = {200, 210};
static float currentRad = 0.0f;

void updatePlayer( PlaydateAPI *pd )
{
    float crankChange = pd->system->getCrankChange();
    float changeRad = degreeToRadian(crankChange);
    currentRad += changeRad * ROTATE_RATIO;

    struct Vec2 drawDir = {0};
    rotateVec2(&DRAW_DIR_BASE, currentRad, &drawDir);
    pd->graphics->drawLine(
            plPos.x, plPos.y,
            plPos.x + drawDir.x, plPos.y + drawDir.y,
            3, kColorBlack);

    PDButtons pushed;
    pd->system->getButtonState(NULL, &pushed, NULL);
    if ( pushed & kButtonA || pushed & kButtonB )
    {
        struct Vec2 vel = {0};
        rotateVec2(&BALL_SPEED, currentRad, &vel);
        //addBallPd(plPos.x, plPos.y, vel.x, vel.y);
        addBullet(plPos.x, plPos.y, vel.x, vel.y);
    }
}
