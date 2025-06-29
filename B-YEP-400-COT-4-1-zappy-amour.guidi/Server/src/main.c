/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "../includes/function_connexes.h"
#include "../includes/frees.h"
#include "../includes/command.h"


int main(int argc, char **argv)
{
    servercontrol_t *server = malloc(sizeof(servercontrol_t));
    FDS = malloc(sizeof(struct pollfd) * 1);
    team_t *team = NULL;
    int sign = 0;
    printf("le nombre d'arguments est %d\n", argc);
    init_command_table();
    checkArgs(argc, argv);
    TRANTIME = malloc(sizeof(tranto_t));
    server->team = malloc(sizeof(team_t) * (argc-12));;
    server->game = OFF;
    server->trantoworld = malloc(sizeof(trantoriant_t));
    server->push_back = push_back;
    server->getLife = getLife;
    server->maxid = 0;
    registerArgs(argc, argv, &server);
    server->map_server = init_map(MAPK.x, MAPK.y);
    for (int i = 0; i < server->teamnb; i++) {
        server->team[i].mates = malloc(1 * sizeof(int));
        server->team[i].matescount = 0;   
    }
    spawn_resources(MAPSERVER);
    srand(time(NULL));
    setupSocket(server);
    printf("== TRANTORIAN GATE ==\n\nServer is on port : %d\n", server->port);
    while(true) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &TRANTIME->timedebut);
        sign = poll(FDS, NFDS, 0);
        if (FDS[0].revents & POLLIN) acceptKlients(server);
        for (int i = 1; i < NFDS;) {
            if (FDS[i].revents) {
                if (FDS[i].revents & (POLLERR | POLLHUP)) {
                    cleanTrantor(server, i);
                } else if (FDS[i].revents & POLLIN) {
                    handleIAcmds(server, FDS[i].fd);
                }
                if (i >= NFDS) break;
                if (FDS[i].fd != -1) i++;
            } else {
                i++;
            }
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &TRANTIME->timefin);
        tiManage(server);
    }
    freeServerelements(&server);
    return 0;
}