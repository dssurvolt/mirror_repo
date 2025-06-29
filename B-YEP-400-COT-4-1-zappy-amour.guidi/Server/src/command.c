/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** command.c
*/

#include "../includes/command.h"

CommandFunc_t command_table[CMD_COUNT] = {NULL};

int wrap_coordinate(int value, int max)
{
    if (value < 0)
        return max - 1;
    if (value >= max)
        return 0;
    return value;
}

void move_forward(servercontrol_t *serv, int id)
{
    trantoriant_t *trantoriant = lookTrantorian(serv, id);

    if (!trantoriant || !trantoriant->islive)
        return;

    switch (trantoriant->direction) {
        case 1:
            trantoriant->position.y = wrap_coordinate(trantoriant->position.y - 1,
                serv->map_server->height);
            break;
        case 2:
            trantoriant->position.x = wrap_coordinate(trantoriant->position.x + 1,
                serv->map_server->width);
            break;
        case 3:
            trantoriant->position.y = wrap_coordinate(trantoriant->position.y + 1,
                serv->map_server->height);
            break;
        case 4:
            trantoriant->position.x = wrap_coordinate(trantoriant->position.x - 1,
                serv->map_server->width);
            break;
    }

    if (trantoriant->writeToIA)
        trantoriant->writeToIA(trantoriant, "ok\n");
}

void move_right(servercontrol_t *serv, int id)
{
    trantoriant_t *trantoriant = lookTrantorian(serv, id);

    if (!trantoriant || !trantoriant->islive)
        return;

    trantoriant->direction = (trantoriant->direction % 4) + 1;
    if (trantoriant->writeToIA)
        trantoriant->writeToIA(trantoriant, "ok\n");
}

void move_left(servercontrol_t *serv, int id)
{
    trantoriant_t *trantoriant = lookTrantorian(serv, id);

    if (!trantoriant || !trantoriant->islive)
        return;

    trantoriant->direction = (trantoriant->direction == 1) ? 4 : trantoriant->direction - 1;
    if (trantoriant->writeToIA)
        trantoriant->writeToIA(trantoriant, "ok\n");
}


void init_command_table() 
{   
    command_table[FORWARD] = move_forward;
    command_table[LEFT] = move_left;
    command_table[RIGHT] = move_right;
    command_table[SET_OBJECT] = set_object;
    command_table[INVENTORY] = inventory;
    command_table[TAKE_OBJECT] = take_object;
    command_table[DEATH] = death;
    //command_table[CONNECT_NBR] = connect_nbr;
    //command_table[FORK] = forkk;
    //command_table[LOOK] = look;
    // command_table[EJECT] = eject;
}
