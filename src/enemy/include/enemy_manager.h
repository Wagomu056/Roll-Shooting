//
// Created by 東口拓也 on 2022/06/27.
//

#ifndef ROLL_SHOOTING_ENEMY_MANAGER_H
#define ROLL_SHOOTING_ENEMY_MANAGER_H

#include "pd_api.h"
#include <vec2.h>

#define ENEMY_MAX 8

struct Enemy
{
    struct Vec2 pos;
    struct Vec2 vel;
    LCDSprite* sprite;
};

void initEnemyManager(PlaydateAPI *pd);
void updateEnemies(void);
int removeEnemyBySprite(const LCDSprite* sprite);

#endif //ROLL_SHOOTING_ENEMY_MANAGER_H
