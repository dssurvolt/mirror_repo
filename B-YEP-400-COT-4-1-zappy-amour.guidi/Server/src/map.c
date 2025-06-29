/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: kali-linux]
** File description:
** map.c
*/

#include "../includes/map.h"

#define MAX_RESOURCES 7
#define MAX_PLAYERS 10

static const float RESOURCE_DENSITY[MAX_RESOURCES] = {
    0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05
};

int *inventory_init(int a)
{
    int *inventory = malloc(sizeof(int) * 7);

    inventory[0] = 10; 
    inventory[1] = 0;
    inventory[2] = 0;
    inventory[3] = 0;
    inventory[4] = 0;
    inventory[5] = 0;
    inventory[6] = 0;
    return inventory;
}

Map_t *init_map(int width, int height)
{
    Map_t *map = malloc(sizeof(Map_t));
    Tile **tiles = NULL;

    if (!map)
        return NULL;
    map->width = width;
    map->height = height;
    tiles = malloc(height * sizeof(Tile *));
    if (!tiles)
        return NULL;
    map->tiles = tiles;
    for (int i = 0; i < height; i++) {
        tiles[i] = malloc(width * sizeof(Tile));
        if (!tiles[i])
            return NULL;
        for (int j = 0; j < width; j++) {
            tiles[i][j].x = j;
            tiles[i][j].y = i;
            tiles[i][j].resources = inventory_init(7);
            tiles[i][j].num_players = 0;
            tiles[i][j].trantorid = malloc(sizeof(int));
        }
    }
    return map;
}

void free_map(Map_t *map)
{
    if (!map)
        return;
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++)
            free(map->tiles[i][j].resources);
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}

void spawn_resources(Map_t *map)
{
    int total_tiles;
    int resource_count;

    if (!map)
        return;
    total_tiles = map->width * map->height;
    for (int k = 0; k < MAX_RESOURCES; k++) {
        resource_count = total_tiles * RESOURCE_DENSITY[k];
        for (int i = 0; i < resource_count; i++) {
            int x = rand() % map->width;
            int y = rand() % map->height;
            map->tiles[y][x].resources[k]++;
        }
    }
}