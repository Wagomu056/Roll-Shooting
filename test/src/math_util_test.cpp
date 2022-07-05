//
// Created by 東口拓也 on 2022/06/20.
//
#include <cmath>
#include "gtest/gtest.h"

extern "C" {
#include <math_util.h>
}

bool equalf(float a, float b)
{
   return (fabs(a - b) <= 0.01f);
}

TEST(Math, rotate) {
    struct Vec2 vec = {1.0f, 0.0f};
    struct Vec2 out = {0.0f, 0.0f};

    rotateVec2(&vec, M_PI_2, &out);
    EXPECT_TRUE(equalf(out.x, 0.0f));
    EXPECT_TRUE(equalf(out.y, 1.0f));

    rotateVec2(&vec, M_PI, &out);
    EXPECT_TRUE(equalf(out.x, -1.0f));
    EXPECT_TRUE(equalf(out.y, 0.0f));

    rotateVec2(&vec, M_PI_4, &out);
    printf("%f\n", out.x);
    printf("%f\n", out.y);
    EXPECT_TRUE(equalf(out.x, 0.7f));
    EXPECT_TRUE(equalf(out.y, 0.7f));
}

TEST(Math, degToRad)
{
    float rad = degreeToRadian( 90.0f );
    EXPECT_TRUE(equalf(rad, 1.57079632679f));
}

TEST(Math, clamp)
{
    float value = 5;
    value = clamp(value, 0, 10);
    EXPECT_EQ(value, 5);

    value = -1;
    value = clamp(value, 0, 10);
    EXPECT_EQ(value, 0);

    value = 20;
    value = clamp(value, 0, 10);
    EXPECT_EQ(value, 10);

    value = 0;
    value = clamp(value, 0, 10);
    EXPECT_EQ(value, 0);

    value = 10;
    value = clamp(value, 0, 10);
    EXPECT_EQ(value, 10);
}
