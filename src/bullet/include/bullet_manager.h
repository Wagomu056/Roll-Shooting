//
// Created by 東口拓也 on 2022/06/25.
//

#ifndef ROLL_SHOOTING_BULLET_MANAGER_H
#define ROLL_SHOOTING_BULLET_MANAGER_H

#include "pd_api.h"

#define BULLET_MAX 64

void initBulletManager(PlaydateAPI *pd);
void updateBullets(void);
void addBullet(float x, float y, float vx, float vy);

#endif //ROLL_SHOOTING_BULLET_MANAGER_H
