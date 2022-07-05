//
// Created by 東口拓也 on 2022/06/25.
//

#include "include/bullet_manager.h"
#include "include/bullet.h"
#include "log.h"
#include "pd_util.h"
#include "util.h"
#include "collision_defines.h"
#include "enemy_manager.h"

static PlaydateAPI* _pd = NULL;
static LCDBitmap *_ballImage = NULL;

static struct Bullet _bullets[BULLET_MAX] = {0};
static LCDSprite *_sprites[BULLET_MAX] = {NULL};
static int _bulletNum = 0;
static int _bulletWidthHalf = 0;
static int _bulletHeightHalf = 0;

static void removeBullet(int index);

void initBulletManager(PlaydateAPI *pd)
{
    _pd = pd;
    _ballImage = loadImageAtPath(pd, "images/bullet.png");

    int w, h;
    for (int i = 0; i < BULLET_MAX; i++)
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->graphics->getBitmapData(_ballImage, &w, &h,
                                     NULL, NULL, NULL);
        _pd->sprite->setImage(sprite, _ballImage, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 999);

        PDRect cr = PDRectMake(0, 0, w, h);
        _pd->sprite->setCollideRect(sprite, cr);
        _pd->sprite->setTag(sprite, kPlayerBullet);

        _sprites[i] = sprite;
    }

    _bulletWidthHalf = w / 2;
    _bulletHeightHalf = h / 2;
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

        int len;
        SpriteCollisionInfo *cInfo = _pd->sprite->moveWithCollisions(bullet->sprite,
                                                                     bullet->pos.x, bullet->pos.y,
                                                                     NULL, NULL, &len);
        for (int i = 0; i < len; i++)
        {
            LCDSprite* other = cInfo[i].other;
            if (_pd->sprite->getTag(other) == kEnemy)
            {
                removeEnemyBySprite(other);
                LOG("Hit removeEnemy");
            }
        }
        _pd->system->realloc(cInfo, 0); 	// free memory of array returned by moveWithCollisions()
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
