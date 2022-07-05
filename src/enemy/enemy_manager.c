//
// Created by 東口拓也 on 2022/06/27.
//

#include "include/enemy_manager.h"
#include "log.h"
#include "pd_util.h"
#include "util.h"
#include "defines.h"
#include "collision_defines.h"

static PlaydateAPI* _pd = NULL;
static LCDBitmap *_enemyImage = NULL;

static struct Enemy _enemies[ENEMY_MAX] = {0};
static LCDSprite *_sprites[ENEMY_MAX] = {NULL};
static int _enemyNum = 0;
static int _enemyWidthHalf = 0;
static int _enemyHeightHalf = 0;
static int _toEnemyAddCount = 0;

static void removeEnemy(int index);

void initEnemyManager(PlaydateAPI *pd)
{
    _pd = pd;
    _enemyImage = loadImageAtPath(pd, "images/enemy.png");

    int w, h;
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        LCDSprite *sprite = _pd->sprite->newSprite();
        _pd->graphics->getBitmapData(_enemyImage, &w, &h,
                                     NULL, NULL, NULL);
        _pd->sprite->setImage(sprite, _enemyImage, kBitmapUnflipped);
        _pd->sprite->setZIndex(sprite, 999);

        PDRect cr = PDRectMake(0, 0, w, h);
        _pd->sprite->setCollideRect(sprite, cr);
        _pd->sprite->setTag(sprite, kEnemy);

        _sprites[i] = sprite;
    }

    _enemyWidthHalf = w / 2;
    _enemyHeightHalf = h / 2;
}

static void addEnemy(float x, float y, float vx, float vy)
{
    if (_enemyNum >= ENEMY_MAX) { return; }
    LOG("AddEnemy: %d:%d", (int)x, (int)y );

    struct Enemy *enemy = &(_enemies[_enemyNum]);
    LCDSprite *sprite = _sprites[_enemyNum];
    enemy->sprite = sprite;
    enemy->pos.x = x;
    enemy->pos.y = y;
    enemy->vel.x = vx;
    enemy->vel.y = vy;

    _pd->sprite->moveTo(sprite, enemy->pos.x, enemy->pos.y);
    _pd->sprite->addSprite(sprite);

    _enemyNum++;
}

static void updateEnemiesMove(void)
{
    for (int i = 0; i < _enemyNum; i++)
    {
        struct Enemy* enemy = &(_enemies[i]);
        enemy->pos.x += enemy->vel.x;
        enemy->pos.y += enemy->vel.y;

        if (isOutArea(&enemy->pos, _enemyWidthHalf, _enemyHeightHalf))
        {
            removeEnemy(i);
            continue;
        }

        _pd->sprite->moveTo(enemy->sprite,
                            enemy->pos.x, enemy->pos.y);
    }
}

const static float ENEMY_SPEED = 1.5f;
const static int ENEMY_SPEED_RANGE = 10;
const static int ADD_ENEMY_HEIGHT_RANGE = 50;
const static int ADD_ENEMY_INTERVAL_RANGE = 90;
static void updateAddEnemies(void)
{
    _toEnemyAddCount--;
    if (_toEnemyAddCount > 0) {
        return;
    }

    const int rnd = rand() % ADD_ENEMY_HEIGHT_RANGE;
    const float speed = ENEMY_SPEED + ((rand() % ENEMY_SPEED_RANGE) * 0.1f);
    addEnemy( DISPLAY_WIDTH + _enemyWidthHalf - 1.0f, _enemyHeightHalf + rnd,
            -1.0f * speed, 0.0f );

    _toEnemyAddCount = 30 + (rand() % ADD_ENEMY_INTERVAL_RANGE);
}

void updateEnemies(void)
{
    updateAddEnemies();
    updateEnemiesMove();
}

static void removeEnemy(int index)
{
    if (index >= _enemyNum) { return; }

    _pd->sprite->removeSprite(_enemies[index].sprite);

    _enemies[index] = _enemies[_enemyNum - 1];

    LCDSprite *sprite = _sprites[index];
    _sprites[index] = _sprites[_enemyNum - 1];
    _sprites[_enemyNum - 1] = sprite;

    _enemyNum--;
}

int removeEnemyBySprite(const LCDSprite* sprite)
{
    for (int i = 0; i < _enemyNum; i++)
    {
        if (_enemies[i].sprite == sprite)
        {
            removeEnemy(i);
            return i;
        }
    }

    return -1;
}

