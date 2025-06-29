
/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** inventory.c
*/

#include "../includes/command.h"
#include "../includes/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int get_resource_index(const char *name)
{
    if (strcmp(name, "food") == 0)
        return 0;
    if (strcmp(name, "linemate") == 0)
        return 1;
    if (strcmp(name, "deraumere") == 0)
        return 2;
    if (strcmp(name, "sibur") == 0)
        return 3;
    if (strcmp(name, "mendiane") == 0)
        return 4;
    if (strcmp(name, "phiras") == 0)
        return 5;
    if (strcmp(name, "thystame") == 0)
        return 6;
    return -1;
}


bool take_resource(Map_t *server, int trantorian_id, int resource_type)
{
    trantoriant_t *trantoriant;
    int x;
    int y;

    if (!server || trantorian_id < 0)
        return false;
    trantoriant = find_trantorian(server, trantorian_id);
    if (!trantoriant)
        return false;
    x = trantoriant->position.x;
    y = trantoriant->position.y;
    if (resource_type < 0 || resource_type >= MAX_RESOURCES)
        return false;
    if (server->tiles[y][x].resources[resource_type] > 0) {
        server->tiles[y][x].resources[resource_type]--;
        trantoriant->inventory[resource_type]++;
        if (trantoriant->writeToIA)
            trantoriant->writeToIA(trantoriant, "ok\n");
            printf("pour take ca va\n");
        return true;
    }
    if (trantoriant->writeToIA)
        trantoriant->writeToIA(trantoriant, "ko\n");
    return false;
}

void take_object(servercontrol_t *server, int id)
{
    trantoriant_t *tranto = lookTrantorian(server, id);
    
    if (!tranto)
        return;
    int index = get_resource_index(server->tab);
    if (index != -1)
        take_resource(server->map_server, id, index);
    else
        tranto->writeToIA(tranto, "ko\n");  

}

bool drop_resource(Map_t *server, int trantorian_id, int resource_type)
{
    printf("Bienvenue dans drop en question\n");
    trantoriant_t *trantoriant;
    int x;
    int y;

    if (!server || trantorian_id < 0)
        return false;
    trantoriant = find_trantorian(server, trantorian_id);
    if (!trantoriant)
        return false;
    x = trantoriant->position.x;
    y = trantoriant->position.y;
    if (resource_type < 0 || resource_type >= MAX_RESOURCES)
        return false;
    if (trantoriant->inventory[resource_type] > 0) {
        trantoriant->inventory[resource_type]--;
        server->tiles[y][x].resources[resource_type]++;
        if (trantoriant->writeToIA)
            trantoriant->writeToIA(trantoriant, "ok\n");
            printf("pour drop ca va\n");
        return true;
    }
    if (trantoriant->writeToIA)
        trantoriant->writeToIA(trantoriant, "ko\n");
    return false;
}


void set_object(servercontrol_t *server, int id)
{
    printf("iciciiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii emma = %s\n", server->tab);
    trantoriant_t *tranto = lookTrantorian(server, id);
    
    if (!tranto)
        return;
    int index = get_resource_index(server->tab);
    printf("index = %d\n", index);
    if (index != -1)
        drop_resource(server->map_server, id, index);
    else
        tranto->writeToIA(tranto, "ko\n");  

}