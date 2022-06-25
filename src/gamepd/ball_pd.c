//
// Created by 東口拓也 on 2022/06/18.
//
#include <stdio.h>

#include <defines.h>

#include "include/ball_pd.h"
#include "ball_core.h"

int ballHeight = 0;

static PlaydateAPI* _pd = NULL;
static LCDBitmap *ballImage = NULL;

static LCDSprite *_ball_sprites[BALL_MAX] = {NULL};
static struct Ball *_balls[BALL_MAX] = {NULL};
static int _ball_num = 0;

static LCDBitmap *loadImageAtPath(PlaydateAPI* pd, const char *path)
{
    const char *outErr = NULL;
    LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
    if ( outErr != NULL ) {
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}

void initializeBallPd(PlaydateAPI *pd)
{
    _pd = pd;
    ballImage = loadImageAtPath(pd, "images/bullet.png");
}

void addBallPd(int x, int y, int vx, int vy)
{
    if (_ball_num >= BALL_MAX) return;

    struct Ball *ball = createBall(x, y, vx, vy);

    LCDSprite *sprite = _pd->sprite->newSprite();
    int w, h;
    _pd->graphics->getBitmapData(ballImage, &w, &h, NULL, NULL, NULL);
    _pd->sprite->setImage(sprite, ballImage, kBitmapUnflipped);

    _pd->sprite->moveTo(sprite, ball->pos.x, ball->pos.y);
    _pd->sprite->setZIndex(sprite, 999);
    _pd->sprite->addSprite(sprite);

    _balls[_ball_num] = ball;
    _ball_sprites[_ball_num] = sprite;

    _ball_num++;
}

static int _li;
void updateBallPd(void)
{
    updateBall();

    for (_li = 0; _li < _ball_num; _li++)
    {
        _pd->sprite->moveTo(_ball_sprites[_li],
                            _balls[_li]->pos.x, _balls[_li]->pos.y);
    }
}
