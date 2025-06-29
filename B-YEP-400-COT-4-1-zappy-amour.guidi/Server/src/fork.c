/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** command.c
*/

#include "../includes/server.h"
#include "../includes/command.h"
#include "../includes/trantorian.h"

egg_t *init_egg(servercontrol_t *serv, int id)
{
    trantoriant_t *trant = malloc(sizeof(trantoriant_t));
    egg_t *new_egg = malloc(sizeof(egg_t));
    int next_egg_id = 1;

    if (!new_egg)
        return NULL;
    trant = lookTrantorian(serv, id);
    new_egg->id = next_egg_id++;
    new_egg->x = trant->position.x;
    new_egg->y = trant->position.y;
    new_egg->team_name = strdup(trant->teams);
    new_egg->hatched = false;
    new_egg->next = NULL;
    return new_egg;
}

void add_egg(egg_t **base, egg_t *new_egg)
{
    egg_t *current = NULL;
    
    if (!base || !new_egg)
        return;
    if (*base == NULL)
        *base = new_egg;
    current = *base;
    while (current->next != NULL)
        current = current->next;
    current->next = new_egg;
}

void add_egg_to_team(servercontrol_t *serv, int id)
{
    int count = 0;
    egg_t *new_egg = NULL;
    
     if (!serv)
        return;
    new_egg = init_egg(serv, id);    
    if (!new_egg)
        return;
    add_egg(&serv->eggs, new_egg);
    if (find_team_by_name(serv, serv->eggs->team_name)) {
        count = count_client(serv, serv->eggs->team_name);
        serv->teamclients++;
    }
}

void fork_command(servercontrol_t *serv, int id)
{
    if (!serv)
        return;
    add_egg_to_team(serv, id);
    //dprintf(id, "ok\n");
    //writeToIA(id, "ok\n");
}
