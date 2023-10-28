#ifndef FISH_H
#define FISH_H

#include "../include/raylib.h"

typedef struct {
    Rectangle box;
    unsigned int speed;
    Texture2D texture[4];
    int type;
}
Fish;

Fish fish_new();
void fish_movement(Fish* f);
bool fish_game_over_condition(Fish* f);

#endif