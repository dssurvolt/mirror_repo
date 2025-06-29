/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** command.h
*/

#ifndef COMMAND_ZAPPY
    #define COMMAND_ZAPPY

#include "server.h"


typedef enum {
    FORWARD = 1, 
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    DEATH,
    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION,
    CMD_COUNT
} All_Command_t;


typedef void (*CommandFunc_t )(servercontrol_t *serv, int id);
extern CommandFunc_t command_table[CMD_COUNT];

int wrap_coordinate(int value, int max);
void init_command_table();
void look(servercontrol_t *serv);
void death(servercontrol_t *server, int id);
void set_object(servercontrol_t *server, int id);
void eject_players(servercontrol_t *serv, int id);
void move_left(servercontrol_t *serv, int id);
void inventory(servercontrol_t *serv, int id);
void move_right(servercontrol_t *serv, int id);
void take_object(servercontrol_t *serv, int id);
void move_forward(servercontrol_t *serv, int id);
void fork_command(servercontrol_t *serv, int id);
int count_client(servercontrol_t *serv, char *name);
bool find_team_by_name(servercontrol_t *serv, char *name);
void connect_nbr(servercontrol_t *serv, int id, char *name);
#endif