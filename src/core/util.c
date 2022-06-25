//
// Created by 東口拓也 on 2022/06/25.
//

#include "include/util.h"
#include "defines.h"

int isOutArea(const struct Vec2* pos, int widthHalf, int heightHalf)
{
    if (pos->y <= -heightHalf) return 1;
    if (pos->y >= DISPLAY_HEIGHT + heightHalf) return 1;
    if (pos->x <= -widthHalf) return 1;
    if (pos->x >= DISPLAY_WIDTH + widthHalf) return 1;
    return 0;
}