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

TEST(Ball, reflect_down)
{
    struct Ball* b = createBall(100, 200, 0, 1);

    // to down
    int i;
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 100);
        EXPECT_EQ(b->pos.y, 200 + i);
        updateBall();
    }

    // reflect and up
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 100);
        EXPECT_EQ(b->pos.y, 220 - i);
        updateBall();
    }
}

TEST(Ball, reflect_up)
{
    struct Ball* b = createBall(100, 20, 0, -1);

    // to up
    int i;
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 100);
        EXPECT_EQ(b->pos.y, 20 - i);
        updateBall();
    }

    EXPECT_EQ(b->pos.y, 0);

    // reflect and down
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 100);
        EXPECT_EQ(b->pos.y, i);
        updateBall();
    }
}

TEST(Ball, reflect_right)
{
    struct Ball* b = createBall(360, 100, 1, 0);

    // to right
    int i;
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 360 + i);
        EXPECT_EQ(b->pos.y, 100);
        updateBall();
    }

    // reflect and left
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 380 - i);
        EXPECT_EQ(b->pos.y, 100);
        updateBall();
    }
}

TEST(Ball, reflect_left)
{
    struct Ball* b = createBall(20, 100, -1, 0);

    // to left
    int i;
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, 20 - i);
        EXPECT_EQ(b->pos.y, 100);
        updateBall();
    }

    EXPECT_EQ(b->pos.x, 0);

    // reflect and right
    for (i = 0; i < 20; i++)
    {
        EXPECT_EQ(b->pos.x, i);
        EXPECT_EQ(b->pos.y, 100);
        updateBall();
    }
}
