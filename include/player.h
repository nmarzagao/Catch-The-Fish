#ifndef PLAYER_H
#define PLAYER_H

#include "../include/raylib.h"
#include "../include/fish.h"

typedef struct {
    Rectangle box;
    float speed;
    unsigned long score;
    Texture2D texture;
}
Player;

Player player_new();
void player_controller(Player* player);
void player_screen_colisions(Player* player);
void player_point_colision(Player* player, Fish* fish);


#endif