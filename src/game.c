#include "../include/game.h"

GameState game_main_menu() {
    // INIT
    ScreenAssets assests = assests_load("./resources/menu.png", (Color) {42, 88, 79, 1});

    while(1) {
        // UPDATE
        if (IsKeyDown( KEY_SPACE )) return PLAY;
        if (IsKeyDown( KEY_Q )) return EXIT_GAME;

        // DRAW
        BeginDrawing();
            ClearBackground(assests.background);
            DrawTexture(assests.texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText("Press Space To Start", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 160, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 200, 20, RAYWHITE);
        EndDrawing();
    }
}



GameState game_start(unsigned long* final_score) {

    // INIT
    ScreenAssets assests = assests_load("./resources/ground.png", (Color) {42, 88, 79, 1});

    // Initialize game structures
    Player player = player_new();
    Fish fish = fish_new();    

    int qtd_sf = GetScreenHeight();
    Snowflake s[qtd_sf];

    for (int i = 0; i < qtd_sf; i++) {
        s[i].y = GetRandomValue(0, -(GetScreenHeight()));
        s[i].x = GetRandomValue(0, GetScreenWidth());
    }



    while (1) {
        // UPDATE
        // player update
        player_controller(&player);
        player_screen_colisions(&player);

        // fish movement
        fish_movement(&fish);

        // Game over condition
        if (fish_game_over_condition(&fish)) {
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


        // Point system
        player_point_colision(&player, &fish);

        // DRAW
       
        BeginDrawing();

            ClearBackground(assests.background);

            DrawTexture(assests.texture, 1, (GetScreenHeight() / 1.3f) + 64, WHITE);

            DrawTexture(fish.texture[fish.type], fish.box.x, fish.box.y, WHITE);
            DrawTexture(player.texture, player.box.x, player.box.y, WHITE);
            
            DrawText(TextFormat("Score: %d", player.score), 10, 10, 20, RAYWHITE);

            for (int i = 0; i < qtd_sf; i++) DrawPixel(s[i].x, s[i].y, RAYWHITE); 

        EndDrawing();
       
    }
}

GameState game_over(unsigned long final_score) {
    // INIT
    ScreenAssets assests = assests_load("./resources/over.png", (Color) {47, 20, 47, 1});

    while(1) {
        // UPDATE
        if (IsKeyDown( KEY_SPACE )) return PLAY;
        if (IsKeyDown( KEY_Q )) return EXIT_GAME;

        // DRAW
        BeginDrawing();
            ClearBackground(assests.background);
            DrawTexture(assests.texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText(TextFormat("Your Score was: %d", final_score), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 40, 20, RAYWHITE);
            DrawText("Press Space To Restart", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 120, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 160, 20, RAYWHITE);
        EndDrawing();
    }
}