
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "player/include/player.h"
#include "bullet/include/bullet_manager.h"
#include "enemy_manager.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static PlaydateAPI* _pd;

int update(void* ud)
{
    updateBullets();
    updateEnemies();
    _pd->sprite->updateAndDrawSprites();

    updatePlayer(_pd);

    return 1;
}

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        _pd = pd;
        pd->system->setUpdateCallback(update, NULL);

        initBulletManager(pd);
        initEnemyManager(pd);
    }

    return 0;
}