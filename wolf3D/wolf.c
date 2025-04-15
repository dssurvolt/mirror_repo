// --- wolf3d_bootstrap.c ---
// All tasks from steps 1 to 4 implemented and ready to compile

#include <SFML/Graphics.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <stdio.h>

#define TILE_SIZE 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define WIDTH 800
#define HEIGHT 600
#define FOV (M_PI / 3)
#define NUM_RAYS 800

// Global map representation
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
};

typedef struct {
    float x;
    float y;
    float angle;
} Player;

void init_player(Player *player) {
    player->x = 3.5 * TILE_SIZE;
    player->y = 3.5 * TILE_SIZE;
    player->angle = M_PI / 2;
}

int is_wall(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    return map[y][x] == 1;
}

void draw_floor_and_ceiling(sfRenderWindow *window) {
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){WIDTH, HEIGHT / 2});

    sfRectangleShape_setFillColor(rect, sfBlue);
    sfRectangleShape_setPosition(rect, (sfVector2f){0, 0});
    sfRenderWindow_drawRectangleShape(window, rect, NULL);

    sfRectangleShape_setFillColor(rect, sfGreen);
    sfRectangleShape_setPosition(rect, (sfVector2f){0, HEIGHT / 2});
    sfRenderWindow_drawRectangleShape(window, rect, NULL);

    sfRectangleShape_destroy(rect);
}

float cast_single_ray(Player player, float ray_angle, sfRenderWindow *window) {
    float ray_x = player.x;
    float ray_y = player.y;

    while (1) {
        ray_x += cos(ray_angle) * 0.1f;
        ray_y += sin(ray_angle) * 0.1f;

        int map_x = (int)(ray_x / TILE_SIZE);
        int map_y = (int)(ray_y / TILE_SIZE);

        if (is_wall(map_x, map_y))
            break;
    }

    float dx = ray_x - player.x;
    float dy = ray_y - player.y;
    return sqrt(dx * dx + dy * dy);
}

void render_wall_column(sfRenderWindow *window, int column, float wall_height, sfColor color) {
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){1, wall_height});
    sfRectangleShape_setFillColor(rect, color);
    sfRectangleShape_setPosition(rect, (sfVector2f){column, (HEIGHT - wall_height) / 2});
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    sfRectangleShape_destroy(rect);
}

void cast_all_rays(sfRenderWindow *window, Player player) {
    float start_angle = player.angle - (FOV / 2);
    float angle_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        float ray_angle = start_angle + i * angle_step;
        float raw_distance = cast_single_ray(player, ray_angle, window);
        float corrected_dist = raw_distance * cos(ray_angle - player.angle);
        float wall_height = (TILE_SIZE / corrected_dist) * (WIDTH / 2);
        sfColor color = sfColor_fromRGB(255 - (int)(corrected_dist * 2), 0, 0);
        render_wall_column(window, i, wall_height, color);
    }
}

void update_player(Player *player) {
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->x += cos(player->angle) * 4;
        player->y += sin(player->angle) * 4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->x -= cos(player->angle) * 4;
        player->y -= sin(player->angle) * 4;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->angle -= 0.05;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player->angle += 0.05;
    }

    int tile_x = (int)(player->x / TILE_SIZE);
    int tile_y = (int)(player->y / TILE_SIZE);

    if (is_wall(tile_x, tile_y)) {
        player->x -= cos(player->angle) * 4;
        player->y -= sin(player->angle) * 4;
    }
}

int main() {
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode){WIDTH, HEIGHT, 32}, "Wolf3D", sfResize | sfClose, NULL);
    Player player;
    init_player(&player);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        update_player(&player);
        sfRenderWindow_clear(window, sfBlack);
        draw_floor_and_ceiling(window);
        cast_all_rays(window, player);
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
