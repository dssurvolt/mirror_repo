/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** frees.c
*/

#include "../includes/frees.h"

void freetrantorians(trantoriant_t **tranto)
{
    trantoriant_t *current = (*tranto);
    trantoriant_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free(current->teams);
        free(current);
        current = tmp;
    }
}


void freeServerelements(servercontrol_t **server)
{
    free((*server)->fds);
    for (int i = 0; i < (*server)->teamnb; i++) {
        free((*server)->team[i].name);
    }
    free((*server)->team);
    freetrantorians(&(*server)->trantoworld);
    free((*server));
}
