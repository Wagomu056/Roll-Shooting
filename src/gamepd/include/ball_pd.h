//
// Created by 東口拓也 on 2022/06/18.
//

#ifndef BOUND_BALL_BALL_PD_H
#define BOUND_BALL_BALL_PD_H

#include "pd_api.h"

void initializeBallPd(PlaydateAPI *pd);
void updateBallPd(void);
void addBallPd(int x, int y, int vx, int vy);

#endif //BOUND_BALL_BALL_PD_H
