/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** command.c
*/


#include "../includes/map.h"

void death(servercontrol_t *server, int id)
{
    trantoriant_t *tranto = lookTrantorian(server, id);

    if (!server || !tranto) {
        if (tranto && tranto->writeToIA)
            tranto->writeToIA(tranto, "ko\n");
        return;
    }

    if (!tranto->islive) {
        tranto->writeToIA(tranto, "ko\n");
        return;
    }

    tranto->islive = false;
    tranto->writeToIA(tranto, "ok\n");
    printf("Le joueur %d est mort.\n", id);
}
