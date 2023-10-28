#include "../include/game.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/* 
TODO:
    Implament a scoreboard
    Fix snow
    Fixup github
    Add more gamemodes
*/


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Catch The Fish");
    SetTargetFPS(60);    

    GameState current_game_state = MAIN_MENU;
    bool should_exit = false;
    unsigned long player_final_score = 0;
    
    while(!should_exit) {
        switch(current_game_state) {
            case MAIN_MENU:
                current_game_state = game_main_menu();
                break;
            case PLAY:
                current_game_state = game_start(&player_final_score);
                break;
            case GAME_OVER:
                current_game_state = game_over(player_final_score);
                break;
            case EXIT_GAME:
                should_exit = true;
                break;
            default:
                printf("ERROR: invalid state!\n");
                exit(1);
        }
    }
    
    CloseWindow();
    return 0;
}