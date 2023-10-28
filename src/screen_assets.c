#include "../include/screen_assets.h"

ScreenAssets assests_load(const char* img_path, const Color c) {
    ScreenAssets s;
    
    Image image = LoadImage(img_path);
    s.texture = LoadTextureFromImage(image);
    UnloadImage(image);

    s.background = (Color) c;

    return s;
}