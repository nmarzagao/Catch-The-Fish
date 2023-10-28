#include "../include/player.h"

Player player_new() {
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

void player_controller(Player* player) {
    if (IsKeyDown( KEY_RIGHT )) player->box.x += player->speed;
    else if (IsKeyDown( KEY_D )) player->box.x += player->speed;

    if (IsKeyDown( KEY_LEFT )) player->box.x -= player->speed;
    else if (IsKeyDown (KEY_A )) player->box.x -= player->speed;
}

void player_screen_colisions(Player* player) {
    if ((player->box.x + player->box.width) >= GetScreenWidth()) {
        player->box.x = GetScreenWidth() - player->box.width;
    }
    else if (player->box.x <= 0) player->box.x = 0;
}

void player_point_colision(Player* player, Fish* fish) {
    bool collision = CheckCollisionRecs(fish->box, player->box);

    // player colision with fish
    if (collision) {
        player->score += 1;
        fish->box.x = GetRandomValue(10, GetScreenWidth() - 10);
        fish->box.y = -20;

        // speed up logic
        if (player->score % 3 == 0) {
            if (fish->speed != 5) fish->speed += 1;
        }

        fish->type = GetRandomValue(0, 3);
    }
}