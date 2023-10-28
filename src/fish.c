#include "../include/fish.h"

Fish fish_new() {
    Fish f;

    f.box.x = GetRandomValue(5, GetScreenWidth() - 5);
    f.box.y = -20;
    f.box.width = 32;
    f.box.height = 32;

    f.speed = 1;

    Image fish_image;
    for (int i = 0; i < 4; i++) {
        fish_image = LoadImage(TextFormat("resources/fish_%d.png", i + 1));
        f.texture[i] = LoadTextureFromImage(fish_image);
        UnloadImage(fish_image);
    }

    return f;
}