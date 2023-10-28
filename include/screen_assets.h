#ifndef SCREEN_ASSETS_H
#define SCREEN_ASSETS_H

#include "../include/raylib.h"

typedef struct {
    Texture2D texture;
    Color background;
}
ScreenAssets;

ScreenAssets assests_load(const char* img_path, const Color c);

#endif