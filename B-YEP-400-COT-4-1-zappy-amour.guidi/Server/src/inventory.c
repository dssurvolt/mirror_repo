
/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** inventory.c
*/

#include "../includes/map.h"

void inventory(servercontrol_t *serv, int trantorian_id)
{
    trantoriant_t *trantoriant = lookTrantorian(serv, trantorian_id);

    if (!trantoriant) {
        printf("Trantorian with id %d not found.\n", trantorian_id);
        trantoriant->writeToIA(trantoriant, "ko\n");
        return;
    }
    printf("[food: %d, ", trantoriant->inventory[0]);
    printf("linemate: %d, ", trantoriant->inventory[1]);
    printf("deraumere: %d, ", trantoriant->inventory[2]);
    printf("sibur: %d, ", trantoriant->inventory[3]);
    printf("mendiane: %d, ", trantoriant->inventory[4]);
    printf("phiras: %d, ", trantoriant->inventory[5]);
    printf("thystame: %d]\n", trantoriant->inventory[6]);
    trantoriant->writeToIA(trantoriant, "ok\n");
}
