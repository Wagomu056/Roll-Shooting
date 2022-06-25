//
// Created by 東口拓也 on 2022/06/25.
//

#include "include/bullet_manager.h"
#include "include/bullet.h"

static PlaydateAPI* _pd = NULL;
static LCDBitmap *_ballImage = NULL;

static struct Bullet _bullets[BULLET_MAX] = {0};
static LCDSprite *_sprites[BULLET_MAX] = {NULL};
static int _bulletNum = 0;
static int _bulletWidth = 0;
static int _bulletHeight = 0;

static LCDBitmap *loadImageAtPath(PlaydateAPI* pd, const char *path);
static void removeBullet(int index);

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

        _pd->sprite->moveTo(bullet->sprite,
                            bullet->pos.x, bullet->pos.y);
    }
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
}

static LCDBitmap *loadImageAtPath(PlaydateAPI* pd, const char *path)
{
    const char *outErr = NULL;
    LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
    if ( outErr != NULL ) {
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}

