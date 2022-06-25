
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "gamepd/include/ball_pd.h"
#include "vec2.h"
#include "math_util.h"
#include "gamepd/include/player_pd.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static PlaydateAPI* _pd;

int update(void* ud)
{
    updateBallPd();
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
        initializeBallPd(pd);
    }

    return 0;
}