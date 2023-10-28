#include <stdlib.h>
#include <stdio.h>
#include "../include/raylib.h"
#include "../include/player.h"
#include "../include/fish.h"
// #include "../include/game.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480


/* 
TODO: 
    Organize Code
    Fix bugs
    Implament a scoreboard
    Fixup github
*/

typedef struct {
    int x;
    int y;
}
Snowflake;

typedef enum {
    MAIN_MENU,
    PLAY,
    GAME_OVER,
    EXIT_GAME
} 
GameState;

GameState game_main_menu();
GameState game_start(unsigned long* final_score);
GameState game_over(unsigned long final_score);

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Catch The Fish");
    SetTargetFPS(60);    

    GameState current_game_state = MAIN_MENU;
    int should_exit = 0;
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
                should_exit = 1;
                break;
            default:
                printf("ERROR: invalid state!\n");
                exit(1);
        }
    }
    
    CloseWindow();
    return 0;
}


GameState game_main_menu() {
    // INIT
    // Background Color
    const Color menu_background_color = {42, 88, 79, 1};

    // Load Main Menu Img
    Image menu_image = LoadImage("resources/menu.png"); 
    Texture2D menu_texture = LoadTextureFromImage(menu_image);
    UnloadImage(menu_image);

    while(1) {
        // UPDATE
        if (IsKeyDown( KEY_SPACE )) return PLAY;
        if (IsKeyDown( KEY_Q )) return EXIT_GAME;

        // DRAW
        BeginDrawing();
            ClearBackground(menu_background_color);
            DrawTexture(menu_texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText("Press Space To Start", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 160, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 200, 20, RAYWHITE);
        EndDrawing();
    }
}



GameState game_start(unsigned long* final_score) {

    // INIT
    // Load ground img
    Image gound_image = LoadImage("resources/ground.png"); 
    Texture2D gound_texture = LoadTextureFromImage(gound_image);
    UnloadImage(gound_image);

    // Initialize background color
    const Color background_color = {42, 88, 79, 1};

    // Initialize game structures
    Player player = player_new();
    Fish fish = fish_new();    


    bool collision = false;    
    int type = GetRandomValue(0, 3); // RANDOM FISH TYPE

    int qtd_sf = GetScreenHeight();
    Snowflake s[qtd_sf];

    for (int i = 0; i < qtd_sf; i++) {
        s[i].y = GetRandomValue(0, -(GetScreenHeight()));
        s[i].x = GetRandomValue(0, GetScreenWidth());
    }



    while (1) {
        // UPDATE
        player_controller(&player);
        player_screen_colisions(&player);


        fish.box.y += fish.speed; 

        if (fish.box.y >= (GetScreenHeight() / 1.3f) + 32) {
            *final_score = player.score;
            return GAME_OVER;
        }

        // snow
        for (int i = 0; i < qtd_sf; i++) {
            s[i].y += 1;
            if (s[i].y >= GetScreenHeight()) {
                s[i].y = GetRandomValue(0, -(GetScreenHeight()));
            }
        }


        // Check boxes collision
        collision = CheckCollisionRecs(fish.box, player.box);


        if (collision) {
            player.score += 1;
            fish.box.x = GetRandomValue(10, GetScreenWidth() - 10);
            fish.box.y = -20;

            if (player.score % 3 == 0) {
                if (fish.speed != 5) fish.speed += 1;
            }

            type = GetRandomValue(0, 3);
        }


        // DRAW
       
        BeginDrawing();

            ClearBackground(background_color);

            DrawTexture(gound_texture, 1, (GetScreenHeight() / 1.3f) + 64, WHITE);

            DrawTexture(fish.texture[type], fish.box.x, fish.box.y, WHITE);
            DrawTexture(player.texture, player.box.x, player.box.y, WHITE);
            
            DrawText(TextFormat("Score: %d", player.score), 10, 10, 20, RAYWHITE);

            for (int i = 0; i < qtd_sf; i++) DrawPixel(s[i].x, s[i].y, RAYWHITE); 

        EndDrawing();
       
    }
}

GameState game_over(unsigned long final_score) {
    // INIT
    Image game_over_image = LoadImage("resources/over.png"); 
    Texture2D game_over_texture = LoadTextureFromImage(game_over_image);
    UnloadImage(game_over_image);

    const Color game_over_background_color = {47, 20, 47, 1};

    while(1) {
        // UPDATE
        if (IsKeyDown( KEY_SPACE )) return PLAY;
        if (IsKeyDown( KEY_Q )) return EXIT_GAME;

        // DRAW
        BeginDrawing();
            ClearBackground(game_over_background_color);
            DrawTexture(game_over_texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText(TextFormat("Your Score was: %d", final_score), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 40, 20, RAYWHITE);
            DrawText("Press Space To Restart", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 120, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 160, 20, RAYWHITE);
        EndDrawing();
    }
}