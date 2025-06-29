/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** trantOnmap.c
*/

#include "../includes/server.h"

void placeTrantorian(servercontrol_t *server, trantoriant_t *tranto)
{
    int n = MAPSERVER->tiles[POSITION.x][POSITION.y].num_players;
    int *temp = realloc(MAPSERVER->tiles[POSITION.x][POSITION.y].trantorid,
    sizeof(int) *(MAPSERVER->tiles[POSITION.x][POSITION.y].num_players + 1));

    MAPSERVER->tiles[POSITION.x][POSITION.y].trantorid = temp;
    MAPSERVER->tiles[POSITION.x][POSITION.y].trantorid[n] = tranto->id;
    MAPSERVER->tiles[POSITION.x][POSITION.y].num_players++;
}