#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include "../include/raylib.h"
#include "../include/player.h"
#include "../include/fish.h"
#include "../include/screen_assets.h"

typedef enum {
    MAIN_MENU,
    PLAY,
    GAME_OVER,
    EXIT_GAME
} 
GameState;


// temporary
typedef struct {
    int x;
    int y;
}
Snowflake;

GameState game_main_menu();
GameState game_start(unsigned long* final_score);
GameState game_over(unsigned long final_score);

#endif