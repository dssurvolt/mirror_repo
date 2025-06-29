/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** serverRegisterArgs.c
*/

#include "../includes/server.h"
#include "../includes/command.h"
#include <time.h>


void registerArgs(int ac, char **av, servercontrol_t **ser)
{
    if (strcmp(av[ac - 2], "-f") == 0) {
        (*ser)->teamnb = ac - 12;
        (*ser)->teamclients = atoi(av[ac-3]);
        (*ser)->frequence = atoi(av[ac-1]);
    } else {
        (*ser)->teamnb = ac - 10;
        (*ser)->teamclients = atoi(av[ac-1]);
        (*ser)->frequence = 100;
    }
    (*ser)->port = atoi(av[2]);
    (*ser)->map.x = atoi(av[4]);
    (*ser)->nfds = 0;
    (*ser)->map.y = atoi(av[6]);
    (*ser)->team = malloc((*ser)->teamnb * sizeof(team_t));
    for(int i = 8; i < ac - 2; i++) {
        printf("%d\n", i);
        (*ser)->team[i % 8].name = strdup(av[i]);
        printf("Team[%d] =>%s\n", i % 8, (*ser)->team[i%8].name);
    }
}

