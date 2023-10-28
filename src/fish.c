#include "../include/fish.h"

Fish fish_new() {
    Fish f;

    f.box.x = GetRandomValue(5, GetScreenWidth() - 5);
    f.box.y = -20;
    f.box.width = 32;
    f.box.height = 32;

    f.type = GetRandomValue(0, 3);
    f.speed = 1;

    Image fish_image;
    for (int i = 0; i < 4; i++) {
        fish_image = LoadImage(TextFormat("resources/fish_%d.png", i + 1));
        f.texture[i] = LoadTextureFromImage(fish_image);
        UnloadImage(fish_image);
    }

    return f;
}

void fish_movement(Fish* f) { f->box.y += f->speed; }

bool fish_game_over_condition(Fish* f) { 
    return (f->box.y >= (GetScreenHeight() / 1.3f) + 32); 
}