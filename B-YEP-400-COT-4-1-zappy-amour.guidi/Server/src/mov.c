/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: kali-linux]
** File description:
** mov.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/command.h"
#include "../includes/map.h"


static void print_map_grid(Map_t *server)
{
    char symbol;
    trantoriant_t *tranto;

    printf("\nMap (%dx%d):\n", server->width, server->height);
    for (int x = 0; x < server->height; x++) {
        for (int y = 0; y < server->width; y++) {
            symbol = '.';
            tranto = server->trantorians;
            while (tranto) {
                if (POSITION.x == x && POSITION.y == y && tranto->islive) {
                    symbol = '0' + tranto->id;
                    break;
                }
                tranto = tranto->next;
            }
            printf("%c ", symbol);
        }
        printf("\n");
    }
}

static void print_tile_details(Map_t *server)
{
    int *player;
    int a = 0;
    for (int x = 0; x < server->height; x++) {
        for (int y = 0; y < server->width; y++) {
            printf("(%d,%d): ", x, y);
            for (int resource = 0; resource < MAX_RESOURCES; resource++)
                printf("%d ", server->tiles[x][y].resources[resource]);
            player = server->tiles[x][y].trantorid = inventory_init(10);
            while (player[a]) {
                printf("P%d ", player[a]);
                a++;
            }
            printf("\n");
        }
    }
}

void print_map_t(Map_t *server)
{
    if (!server || !server->trantorians) {
        printf("No players on the map_t.\n");
        return;
    }
    print_map_grid(server);
    print_tile_details(server);
}

trantoriant_t *find_trantorian(Map_t *server, int trantorian_id)
{
    trantoriant_t *trantoriant = server->trantorians;

    while (trantoriant) {
        if (trantoriant->id == trantorian_id && trantoriant->islive)
            return trantoriant;
        trantoriant = trantoriant->next;
    }
    return NULL;
}

void eject_players(servercontrol_t *server, int trantorian_id)
{
    trantoriant_t *ejector = find_trantorian(MAPSERVER, trantorian_id);
    if (!MAPSERVER || !ejector || !ejector->islive)
        return;

    int x = ejector->position.x;
    int y = ejector->position.y;
    printf("Ejecting players from (%d, %d) by player %d\n", x, y, ejector->id);
    trantoriant_t *currents;
    int a = 0;
    int *current = MAPSERVER->tiles[x][y].trantorid = inventory_init(10);
    //trantoriant_t *next;
    trantoriant_t *next;
    int dx = 0, dy = 0;

    // Direction deltas: 1=N, 2=E, 3=S, 4=W
    switch (ejector->direction) {
        case 1: dy = -1; break;
        case 2: dx = 1; break;
        case 3: dy = 1; break;
        case 4: dx = -1; break;
    }

    // Eject all other players from the tile
    while (current[a]) {
        currents = find_trantorian(MAPSERVER, current[a]);
        next = find_trantorian(MAPSERVER, current[a + 1]);
        if (current[a] != trantorian_id && currents->islive) {
            // Move player to new position with wrapping
            currents->position.x = wrap_coordinate(currents->position.x + dx, MAPSERVER->width);
            currents->position.y = wrap_coordinate(currents->position.y + dy, MAPSERVER->height);
            printf("Ejecting player %d to (%d, %d)\n", find_trantorian(MAPSERVER, current[a])->id,
                   currents->position.x, currents->position.y);

            // Send eject message with the direction the player is coming from
            int from_dir = (ejector->direction + 1) % 4 + 1; // Opposite direction
            char msg[32];
            snprintf(msg, sizeof(msg), "eject: %d\n", from_dir);
            // broadcast_message(&serv->map_server, currents, msg); // Use broadcast_message
        }
        currents = next;
    }

    // Notify ejector
    if (ejector->writeToIA)
        ejector->writeToIA(ejector, "ok\n");
}

// Main function remains commented as per original