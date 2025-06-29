/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** manageWelcome.c
*/

#include "../includes/server.h"

void communika(servercontrol_t *server, char **commands, trantoriant_t *tranto)
{
    int teamrest = 0;
    char buffer[32];
    char message[450];

    for (int i = 0; i < server->teamnb; i++) {
        if (strcmp(server->team[i].name, commands[0]) == 0) {
            teamrest = server->team[i].matescount;
            if (teamrest == server->teamclients) {
                tranto->writeToIA(tranto, "No more slot available\n");
                break;
            }
            snprintf(buffer, sizeof(buffer), "%d\n", TEAMTR - teamrest);
            WRITE(tranto, buffer);
            snprintf(message, sizeof(message), "%d %d\n", MAPK.x, MAPK.y);
            tranto->writeToIA(tranto, message);
            addMates(&server->team[i], tranto->id);
            tranto->teams = strdup(commands[0]);
            tranto->position = tranPosition(server);
            placeTrantorian(server, tranto);
            tranto->islive = true;
            break;
        }
        if (i + 1 == server->teamnb) {
            tranto->writeToIA(tranto, "Donne un vrai nom d'équipe.\n");
            break;
        }
    }
}

void updaPosition(servercontrol_t *server, trantoriant_t *tranto)
{

}