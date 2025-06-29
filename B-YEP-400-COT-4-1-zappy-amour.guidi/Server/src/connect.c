/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** command.c
*/

#include "../includes/command.h"
#include "../includes/server.h"
//je reg sile nom d’équipe demandé par le joueur est égal à une des équipes du serveur ?"

bool find_team_by_name(servercontrol_t *serv, char *name)
{
    if (!serv || !name)
        return false;
        for (int i = 0; i < serv->teamnb; i++) {
        if (serv->team[i].name && 
        strcmp(serv->team[i].name, name) == 0)
            return true;
    }
    return false; 
}

//nombre de client connecté a cette team

int count_client(servercontrol_t *serv, char *name)
{
    if (!serv || !name)
        return 0;

    int count = 0;
    trantoriant_t *tmp = serv->trantoworld;

    while (tmp != NULL) {
        if (tmp->teams && strcmp(tmp->teams, name) == 0)
            count++;
        tmp = tmp->next;
    }
    return count;
}

// Commande connect_nbr : retourne le nombre de slots restants pour une team

void connect_nbr(servercontrol_t *serv, int id , char *name)
{
    if (!serv || !name || !find_team_by_name(serv, name)) {
        dprintf(id, "0\n");
        return;
    }
    int clients = count_client(serv, name);
    int remaining = serv->teamclients - clients;
    if (remaining < 0)
        remaining = 0;
    //writeToIA(id, "ok\n");
    //dprintf(id, "%d\n", remaining);
}


