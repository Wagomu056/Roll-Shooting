//
// Created by 東口拓也 on 2022/06/25.
//

#include "include/pd_util.h"

LCDBitmap *loadImageAtPath(PlaydateAPI* pd, const char *path)
{
    const char *outErr = NULL;
    LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
    if ( outErr != NULL ) {
        pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}