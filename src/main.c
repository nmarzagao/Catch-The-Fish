#include <stdlib.h>
#include "../include/raylib.h"

/* 
TODO: 
    Organize Code
    Fix bugs
    Implament a scoreboard
    Fixup github
*/

int game_menu();
int game_start();
int game_over(unsigned int score);
void player_controller(const float speed, Rectangle* player_box);


typedef struct {
    Rectangle box;
    unsigned int speed;
    Texture2D texture[4];
}
Fish;

typedef struct {
    Rectangle box;
    float speed;
    unsigned long score;
    Texture2D texture;

}
Player;

typedef struct {
    int x;
    int y;
}
Snowflake;

Player init_player();
Fish init_fish();


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Catch The Fish");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    int game_state = game_menu();

    while (game_state != 0) {
        if (game_state == 1) {
            game_state = game_start();
        }
    }
    
    CloseWindow();

    return 0;
}


int game_menu() {
    Color menu_color = {42, 88, 79, 1};

    Image menu_image = LoadImage("resources/menu.png"); 
    Texture2D menu_texture = LoadTextureFromImage(menu_image);
    UnloadImage(menu_image);

    while(1) {
        if (IsKeyDown( KEY_SPACE )) return 1;
        if (IsKeyDown( KEY_Q )) return 0;

        BeginDrawing();
            ClearBackground(menu_color);
            DrawTexture(menu_texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText("Press Space To Start", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 160, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 200, 20, RAYWHITE);
        EndDrawing();
    }
}

Fish init_fish() {
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

Player init_player() {
    Player p;

    p.box.x = GetScreenWidth() / 2.0f - 30;
    p.box.y = GetScreenHeight() / 1.3f;
    p.box.width = 64;
    p.box.height = 64;

    p.speed = 8.0;
    p.score = 0;

    Image player_image = LoadImage("resources/penguin_player.png"); 
    p.texture = LoadTextureFromImage(player_image);
    UnloadImage(player_image);

    return p;
}

int game_start() {

    Image gound_image = LoadImage("resources/ground.png"); 
    Texture2D gound_texture = LoadTextureFromImage(gound_image);
    UnloadImage(gound_image);

    Player player = init_player();

    Fish fish = init_fish();    

    bool collision = false;         // Collision detection 

    Color menu_color = {42, 88, 79, 1}; 
    Color ground_color = {110, 184, 168, 1};

    int state = 0; 

    int type = GetRandomValue(0, 3);

    int qtd_sf = GetScreenHeight();

    Snowflake s[qtd_sf];

    for (int i = 0; i < qtd_sf; i++) {
        s[i].y = GetRandomValue(0, -(GetScreenHeight()));
        s[i].x = GetRandomValue(0, GetScreenWidth());
    }



    while (1) {

        // Update
        if (IsKeyDown( KEY_RIGHT )) player.box.x += player.speed;
        else if (IsKeyDown( KEY_D )) player.box.x += player.speed;

        if (IsKeyDown( KEY_LEFT )) player.box.x -= player.speed;
        else if (IsKeyDown (KEY_A )) player.box.x -= player.speed;

        // colisions
        if ((player.box.x + player.box.width) >= GetScreenWidth()) player.box.x = GetScreenWidth() - player.box.width;
        else if (player.box.x <= 0) player.box.x = 0;


        fish.box.y += fish.speed; 

        if (fish.box.y >= (GetScreenHeight() / 1.3f) + 32) {
            state = game_over(player.score);
            if (state == 0) {
                break;  // Exit the game loop and return to main menu
            } else {
                // Reset player, fish, and collision flag for a new game
                player = init_player();
                fish = init_fish();
                collision = false;
            }
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


        // Draw
       
        BeginDrawing();

            ClearBackground(menu_color);

            DrawTexture(gound_texture, 1, (GetScreenHeight() / 1.3f) + 64, WHITE);

            DrawTexture(fish.texture[type], fish.box.x, fish.box.y, WHITE);
            DrawTexture(player.texture, player.box.x, player.box.y, WHITE);
            
            DrawText(TextFormat("Score: %d", player.score), 10, 10, 20, RAYWHITE);

            for (int i = 0; i < qtd_sf; i++) DrawPixel(s[i].x, s[i].y, RAYWHITE); 

        EndDrawing();
       
    }
}

int game_over(unsigned int score) {
    Image over_image = LoadImage("resources/over.png"); 
    Texture2D over_texture = LoadTextureFromImage(over_image);
    UnloadImage(over_image);

    Color over_color = {47, 20, 47, 1};

    while(1) {

        if (IsKeyDown( KEY_SPACE )) return 1;
        if (IsKeyDown( KEY_Q )) return 0;

        BeginDrawing();
            ClearBackground(over_color);
            DrawTexture(over_texture, GetScreenWidth() / 4 -40, 0, WHITE);
            DrawText(TextFormat("Your Score was: %d", score), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 40, 20, RAYWHITE);
            DrawText("Press Space To Restart", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 120, 20, RAYWHITE);
            DrawText("Press Q To Quit", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 160, 20, RAYWHITE);

        EndDrawing();
    }
}