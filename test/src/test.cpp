//
// Created by 東口拓也 on 2022/06/18.
//
#include "gtest/gtest.h"

extern "C" {
#include <ball_core.h>
}

TEST(Ball, create) {
    struct Ball* b = createBall(11, 22, 0, 0);
    EXPECT_EQ(b->pos.x, 11);
    EXPECT_EQ(b->pos.y, 22);

    struct Ball* b2 = createBall(33, 44, 0, 0);
    EXPECT_EQ(b2->pos.x, 33);
    EXPECT_EQ(b2->pos.y, 44);

    EXPECT_FALSE(b == b2);
}
