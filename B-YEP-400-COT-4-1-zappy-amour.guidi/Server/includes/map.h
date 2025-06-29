/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: kali-linux]
** File description:
** map.h
*/

#ifndef MAP
    #define MAP

#include <stdio.h>
#include <stdlib.h>
#include "trantorian.h"

#define MAX_RESOURCES 7
#define MAX_PLAYERS 10

typedef struct {
    int x, y;  // Coordonnées
    int *resources;  // Tableau des ressources (indexées par type)
    int num_players;  // Nombre de joueurs sur la tuile
    int *trantorid;
} Tile;

typedef struct Map {
    int width, height;  // Dimensions de la carte
    Tile **tiles;  // Matrice de la carte
    struct trantorian *trantorians;
    int num_players;
} Map_t;

Map_t *init_map(int width, int height);
void spawn_resources(Map_t *map);
void print_map(Map_t *map);
bool writeToIA_test(struct trantorian *t, char *message);
void broadcast_message(Map_t **server, struct trantorian *sender, const char *message);
bool take_resource(Map_t *server, int trantorian_id, int resource_type);
int *inventory_init(int a);
trantoriant_t *find_trantorian(Map_t *server, int trantorian_id);
void free_map(Map_t *map);    

#endif