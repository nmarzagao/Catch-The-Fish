#ifndef FISH_H
#define FISH_H

#include "../include/raylib.h"

typedef struct {
    Rectangle box;
    unsigned int speed;
    Texture2D texture[4];
}
Fish;

Fish fish_new();

#endif