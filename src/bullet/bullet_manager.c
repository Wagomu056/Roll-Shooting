//
// Created by 東口拓也 on 2022/06/25.
//

#include "include/bullet_manager.h"
#include "include/bullet.h"
#include "defines.h"
#include "log.h"
#include "pd_util.h"

static PlaydateAPI* _pd = NULL;
static LCDBitmap *_ballImage = NULL;

static struct Bullet _bullets[BULLET_MAX] = {0};
static LCDSprite *_sprites[BULLET_MAX] = {NULL};
static int _bulletNum = 0;
static int _bulletWidth = 0;
static int _bulletWidthHalf = 0;
static int _bulletHeight = 0;
static int _bulletHeightHalf = 0;

static void removeBullet(int index);
static int isOutArea(const struct Vec2* pos, int widthHalf, int heightHalf);

void initBulletManager(PlaydateAPI *pd)
{
    _pd = pd;
    _ballImage = loadImageAtPath(pd, "images/ball.png");

    for (int i = 0; i < BULLET_MAX; i++)
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->graphics->getBitmapData(_ballImage, &_bulletWidth, &_bulletHeight,
                                     NULL, NULL, NULL);
        _pd->sprite->setImage(sprite, _ballImage, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 999);

        _sprites[i] = sprite;
    }

    _bulletWidthHalf = _bulletWidth / 2;
    _bulletHeightHalf = _bulletHeight / 2;
}

void addBullet(float x, float y, float vx, float vy)
{
    if (_bulletNum >= BULLET_MAX) { return; }

    struct Bullet *bullet = &(_bullets[_bulletNum]);
    LCDSprite *sprite = _sprites[_bulletNum];
    bullet->sprite = sprite;
    bullet->pos.x = x;
    bullet->pos.y = y;
    bullet->vel.x = vx;
    bullet->vel.y = vy;

    _pd->sprite->moveTo(sprite, bullet->pos.x, bullet->pos.y);
    _pd->sprite->addSprite(sprite);

    _bulletNum++;
}

void updateBullets(void)
{
    int i;
    for (i = 0; i < _bulletNum; i++)
    {
        struct Bullet* bullet = &(_bullets[i]);
        bullet->pos.x += bullet->vel.x;
        bullet->pos.y += bullet->vel.y;

        if (isOutArea(&bullet->pos, _bulletWidthHalf, _bulletHeightHalf))
        {
            removeBullet(i);
            continue;
        }

        _pd->sprite->moveTo(bullet->sprite,
                            bullet->pos.x, bullet->pos.y);
    }
}

static int isOutArea(const struct Vec2* pos, int widthHalf, int heightHalf)
{
    if (pos->y <= -heightHalf) return 1;
    if (pos->y >= DISPLAY_HEIGHT + heightHalf) return 1;
    if (pos->x <= -widthHalf) return 1;
    if (pos->x >= DISPLAY_WIDTH + widthHalf) return 1;
    return 0;
}

static void removeBullet(int index)
{
    if (index >= _bulletNum) { return; }

    _pd->sprite->removeSprite(_bullets[index].sprite);

    _bullets[index] = _bullets[_bulletNum - 1];

    LCDSprite *sprite = _sprites[index];
    _sprites[index] = _sprites[_bulletNum - 1];
    _sprites[_bulletNum - 1] = sprite;

    _bulletNum--;

    LOG("Remove:%d", index);
}
