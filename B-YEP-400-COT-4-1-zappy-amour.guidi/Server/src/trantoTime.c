/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** trantoTime.c
*/

#include "../includes/trantoTime.h"
#include "../includes/server.h"
#include <stdint.h>


double tiManage(servercontrol_t *server)
{
    TRANTIME->dt = (TRANTIME->timefin.tv_sec  - 
        TRANTIME->timedebut.tv_sec) * 1000000 +
        (TRANTIME->timefin.tv_sec - TRANTIME->timedebut.tv_sec) / 1000;
    uint64_t timefreq = 1000000 / server->frequence;
    int thicks = 0;
    if (timefreq > TRANTIME->dt) {
        getLife(server, 1);
        server->time += 1;
        usleep(timefreq - TRANTIME->dt);
    } else {
        thicks = TRANTIME->dt / timefreq;
        getLife(server, thicks);
        server->time += thicks;
    }
    if (server->time >= 20) {
        spawn_resources(MAPSERVER);
        printf("Ressources spawn again !");
        server->time = 0;
    }
}

void getLife(servercontrol_t *server, int dt)
{
    trantoriant_t *current = server->trantoworld;
    if (current == NULL)
        return;
    for (; current != NULL; current = current->next) {
        if (current->islive == true && current->vie > 0) {
            current->vie -= dt;
            printf("Tranto [%d] a une vie de => %d\n", current->id, current->vie);
        } else if(current->islive == true && current->vie <= 0) {
            current->vie += 126;
            current->inventory[0] -= 1;
            printf("[%d] => %d restant\n", current->fd, current->inventory[0]);
        }
        if (current->teams != NULL && current->inventory[0] <= 0) {
            current->islive = false;
            printf("Ah, l'IA %d est mort\n", current->id);
        }
    }
}

void addMates(team_t *teams, int id)
{
    int *temp = realloc(teams->mates, sizeof(int) * (teams->matescount + 1));

    teams->mates = temp;
    teams->mates[teams->matescount] = id;
    teams->matescount++;
}

position_t tranPosition(servercontrol_t *server)
{
    position_t posima;

    posima.x = 0 + rand() % (server->map.x - 0 + 1); 
    posima.y = 0 + rand() % (server->map.y - 0 + 1);
    return posima;
}